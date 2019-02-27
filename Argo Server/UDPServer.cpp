#include "UDPServer.h"
#include <iostream>
#include <string>
#include <algorithm>

UDPServer::UDPServer()
{
}

UDPServer::~UDPServer()
{
}

std::vector<int> UDPServer::getAvailableLobbies()
{
	std::vector<int> availableLobbies;
	for (int i = 0; i < m_lobbies.size(); ++i) {
		if (m_lobbies[i].m_open && !m_lobbies[i].m_inGame) {
			availableLobbies.push_back(i);
		}
	}
	return availableLobbies;
}

void UDPServer::createLobby()
{
	Lobby lobby;
	m_lobbies.push_back(lobby);
}

int UDPServer::mapToLobby()
{
	auto availableLobbies = getAvailableLobbies();
	if (availableLobbies.empty()) {
		createLobby();
		std::cout << "Create Lobby as none available" << std::endl;
	}
	int clientsPushed = 0;
	int index = 0;
	int lobbyIndex = m_lobbies.size() - 1;
	for (auto client : m_waiting) {
		if (index < MAX_CLIENTS) {
			std::cout << "Mapped: " << client.first << std::endl;
			m_lobbies.back().m_clients.insert(client);
			m_ipToLobby[client.first] = lobbyIndex;
			clientsPushed++;
		}
		else {
			// Leave if not full (allows for lobbies below the maximum amount)
			break;
		}
	}
	auto & lobbyClients = m_lobbies.back().m_clients;
	/*auto pred = [client](std::pair<const std::string, ClientData> & data) {
		return std::find(client.begin(), client.end(), data) != client.end();
	};
	m_waiting.erase(std::remove_if(m_waiting.begin(), m_waiting.end(), pred), m_waiting.end());*/
	for (auto & client : lobbyClients) {
		m_waiting.erase(client.first);
	}
	std::cout << "Removing Clients from waiting" << std::endl;
	return 0;
}

void UDPServer::startLobby(Lobby & lobby)
{
	Packet * p = new Packet;
	ZeroMemory(p, sizeof(struct Packet) + 1);
	p->type = MessageType::START;

	Packet * startMsg = new Packet();
	for (auto & ip : lobby.m_clients) {
		ZeroMemory(startMsg, sizeof(struct Packet));
		startMsg->playerID = ip.second.index;
		startMsg->type = MessageType::START;
		startMsg->numOtherPlayers = lobby.m_clients.size() - 1;
		ClientData & clientData = ip.second;
		int sendResult = sendto(m_listening, (char*)startMsg, sizeof(struct Packet) + 1, 0, (LPSOCKADDR)&clientData.clientAddr, clientData.clientAddrLen);
		if (sendResult == SOCKET_ERROR) {
			std::cerr << "Failed to send: " << WSAGetLastError() << std::endl;
		}
		else {
			char ipSentTo[256];
			ZeroMemory(&ipSentTo, 256);
			inet_ntop(AF_INET, &clientData.clientAddr.sin_addr, ipSentTo, 256);
			std::cout << "Sent message to : " << ipSentTo << ":" << clientData.clientAddr.sin_port << std::endl;
		}
	}
}

void UDPServer::handleLobby(Lobby & lobby, ClientData & current, Packet & p)
{
	for (auto & ipPair : lobby.m_clients) {
		// Send to everyone except yourself
		ClientData & clientData = ipPair.second;
		if (clientData.index != current.index) {
			sockaddr_in & clientAddr = ipPair.second.clientAddr;
			int sendResult = sendto(m_listening, (char*)&p, sizeof(struct Packet) + 1, 0, (LPSOCKADDR)&clientData.clientAddr, sizeof(clientData.clientAddr));
			if (sendResult == SOCKET_ERROR) {
				std::cerr << "Failed to send: " << WSAGetLastError() << std::endl;
			}
			else {
				char ipSentTo[256];
				ZeroMemory(&ipSentTo, 256);
				inet_ntop(AF_INET, &clientAddr.sin_addr, ipSentTo, 256);
				std::cout << "Sent message to : " << ipSentTo << ":" << clientAddr.sin_port << std::endl;
			}
		}
	}
}

bool UDPServer::createSock()
{
	int address_family = AF_INET;
	int type = SOCK_DGRAM;
	int protocol = IPPROTO_UDP;
	m_listening = socket(address_family, type, protocol);
	if (m_listening == INVALID_SOCKET) {
		std::cout << "Can't create a socket" << std::endl;
		exit(EXIT_FAILURE);
		return false;
	}
	else {
		std::cout << "Server created socket" << std::endl;
	}
	return true;
}

bool UDPServer::bindSock()
{
	int address_family = AF_INET;
	m_hint.sin_family = address_family;
	m_hint.sin_port = htons(port);
	inet_pton(m_hint.sin_family, "149.153.106.150", &m_hint.sin_addr);
	if (bind(m_listening, (LPSOCKADDR)&m_hint, sizeof(m_hint)) == SOCKET_ERROR) {
		std::cerr << "Server cannot bind socket: " << WSAGetLastError() << std::endl;
		exit(EXIT_FAILURE);
		return false;
	}
	else {
		std::cout << "Server bound socket" << std::endl;
	}
	return true;
}

bool UDPServer::closeSock()
{
	closesocket(m_listening);
	WSACleanup();
	return true;
}

void UDPServer::messageHandler()
{
	sockaddr_in clientAddr;
	int clientAddrLen = sizeof(sockaddr_in);
	Packet p;
	int addrFamily = AF_INET;
	int numWaiting = 0;
	while (true) {
		std::cout << "Update" << std::endl;
		// Wipe all memoty of previous packets
		ZeroMemory(&clientAddr, clientAddrLen);
		ZeroMemory(&p, sizeof(struct Packet));
		
		// Read packets
		int bytes_recv = recvfrom(m_listening, (char*)&p, sizeof(struct Packet) + 1, 0, (LPSOCKADDR)&clientAddr, &clientAddrLen);
		// Check for critical errors
		if (bytes_recv == SOCKET_ERROR) {
			std::cerr << "Server failed to receive: " << WSAGetLastError() << std::endl;
		}
		else {
			// Actually do some stuff here
			std::string mapping;
			char clientIP[256];
			ZeroMemory(&clientIP, 256);
			// Get the client ip
			inet_ntop(addrFamily, &clientAddr.sin_addr, clientIP, 256);
			mapping = std::string(clientIP)  + ":" + std::to_string(clientAddr.sin_port);
			// Check if IP exisits in waiting
			if (p.type == MessageType::JOINED) {
				ClientData data;
				data.index = numWaiting;
				data.clientAddr = clientAddr;
				data.clientAddrLen = sizeof(clientAddr);
				m_waiting[mapping] = data;
				auto & current = m_waiting[mapping];
				numWaiting++;
				if (numWaiting >= MAX_CLIENTS) {
					mapToLobby();
					numWaiting = 0;
					startLobby(m_lobbies.back());
				}
			}

			// Handle 
			if (!m_ipToLobby.empty()) {
				int lobbyIndex = m_ipToLobby[mapping];
				auto & current = m_lobbies[lobbyIndex].m_clients[mapping];
				handleLobby(m_lobbies[lobbyIndex], current, p);
			}

			std::cout << "Received message from: " << mapping << std::endl;
		}
	}
}
