#include "TCPServer.h"
#include <iostream>
#include <thread>
#include <string>
#include <algorithm>

TCPServer::TCPServer()
{
	m_started = false;
}

TCPServer::~TCPServer()
{
}

std::vector<int> TCPServer::getAvailableLobbies()
{
	std::vector<int> availableLobbies;
	for (int i = 0; i < m_lobbies.size(); ++i) {
		if (m_lobbies[i].m_open && !m_lobbies[i].m_inGame) {
			availableLobbies.push_back(i);
		}
	}
	return availableLobbies;
}

void TCPServer::createLobby()
{
	Lobby lobby;
	//lobby.m_clients.resize(MAX_CLIENTS);
	m_lobbies.push_back(lobby);
}

int TCPServer::mapToLobby()
{
	auto availableLobbies = getAvailableLobbies();
	if (availableLobbies.empty()) {
		createLobby();
		std::cout << "Create Lobby as none available" << std::endl;
	}
	int clientsPushed = 0;
	for (int i = 0; i < MAX_CLIENTS; ++i) {
		if (m_clients.at(i)) {
			std::cout << "Mapped: " << m_clients[i] << std::endl;
			m_lobbies.back().m_clients.push_back(m_clients[i]);
			clientsPushed++;
		}
		else {
			// Leave if not full (allows for lobbies below the maximum amount)
			break;
		}
	}
	auto client = m_lobbies.back().m_clients;
	auto pred = [client](SOCKET & socket) {
		return std::find(client.begin(), client.end(), socket) != client.end();
	};
	m_clients.erase(std::remove_if(m_clients.begin(), m_clients.end(), pred), m_clients.end());
	std::cout << "Removing Clients from waiting" << std::endl;
	return 0;
}

void TCPServer::startLobby(Lobby & lobby)
{
	Packet * p = new Packet;
	ZeroMemory(p, sizeof(struct Packet) + 1);
	p->type = MessageType::START;
	for (int i = 0; i < lobby.m_clients.size(); ++i) {
		p->playerID = i;
		std::vector<int> otherPlayerIDs;
		//otherPlayerIDs = { -1,-1, -1 };
		for (int j = 0; j < lobby.m_clients.size(); ++j) {
			if (i != j) {
				otherPlayerIDs.push_back(j);
			}
		}
		p->numOtherPlayers = otherPlayerIDs.size();
		/*p->otherPlayerIDs = otherPlayerIDs;
		std::cout << sizeof(otherPlayerIDs) << std::endl;*/
		std::cout << "Sending start to :" << lobby.m_clients[i] << std::endl;
		send(lobby.m_clients[i], (char*)p, sizeof(struct Packet) + 1, 0);
	}
}

void TCPServer::update()
{
	acceptConnections();
}

void TCPServer::sendToAllWaiting(Packet * p)
{

}

void TCPServer::sendToAllInLobby(Packet * p, Lobby & lobby)
{
	for (auto & client : lobby.m_clients) {
		send(client, (char*)p, sizeof(struct Packet) + 1, 0);
	}
}

bool TCPServer::createSock()
{
	// Create a socket
	m_listening = socket(AF_INET, SOCK_STREAM, 0);
	if (m_listening == INVALID_SOCKET)
	{
		std::cerr << "Can't create a socket! Quitting" << std::endl;
		return false;
	}
	std::cout << "Socket created" << std::endl;
	return true;
}

bool TCPServer::bindSock()
{
	m_hint.sin_family = AF_INET;
	m_hint.sin_port = htons(port);
	//hint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton .... 
	inet_pton(m_hint.sin_family, "149.153.106.150", &m_hint.sin_addr);

	if (bind(m_listening, (sockaddr*)&m_hint, sizeof(m_hint)) == SOCKET_ERROR) {
		std::cerr << "Cannot bind sock: " << WSAGetLastError() << std::endl;
		exit(EXIT_FAILURE);
		return false;
	}
	std::cout << "Bound socket" << std::endl;
	listen(m_listening, MAX_CLIENTS - 1);
	return true;
}

bool TCPServer::closeSock()
{
	closesocket(m_listening);
	Packet * p = new Packet();
	std::cout << "Close sock" << std::endl;
	for (int i = 0; i < m_numPlayers; ++i) {
		std::cout << "Client num: " << i << "Shutdown sent" << std::endl;
		SOCKET client = m_clients[i];
		send(client, (char*)p, sizeof(Packet) + 1, 0);

		shutdown(client, SD_BOTH);
		closesocket(client);
	}
	WSACleanup();
	return true;
}

void TCPServer::acceptConnections()
{
	int addrSize = sizeof(sockaddr);
	// loop over client connections while not above connection limit
	Packet * p = new Packet();
	while (true) {
		ZeroMemory(p, sizeof(struct Packet));
		if (m_numPlayers != MAX_CLIENTS) {
			m_clients[m_numPlayers] = accept(m_listening, &m_clientAddrs[m_numPlayers], &addrSize);
			if (m_clients[m_numPlayers] != INVALID_SOCKET) {
				m_numPlayers++;
				std::cout << "Num players: " << m_numPlayers << std::endl;
			}
		}
		else if (!m_started) {
			//p->playerID = m_numPlayers + 1;
			//p->type = MessageType::START;
			//for (auto & client : m_clients) {
			//	std::cout << "Server sends start to " << client << std::endl;
			//	int sent = send(client, (char*)p, sizeof(struct Packet) + 1, 0);
			//	/*if (sent <= 0)
			//		break;*/
			//}
			m_started = true;
			mapToLobby();
			if (!m_lobbies.empty()) {
				Lobby & lobby = m_lobbies.back();
				lobby.m_inGame = true;
				if (lobby.m_clients.size() < MAX_CLIENTS) 
				{
					lobby.m_open = true;
				}
				else 
				{
					lobby.m_open = false;
				}
				int numPlayers = lobby.m_clients.size();
				for (int i = 0; i < lobby.m_clients.size(); ++i) {
					std::thread t([&](TCPServer * serv) {
						serv->messageHandler(i, numPlayers, m_lobbies.back().m_clients, m_lobbies.back().m_inGame);
					}, this);
					t.detach();
				}
				startLobby(lobby);
				m_started = false;
				m_numPlayers = 0;
			}
			else {
				m_started = false;
			}
		}
	}
}

void TCPServer::messageHandler(SOCKET sock, int playerCount, std::vector<SOCKET> &clients, bool & started)
{
	SOCKET currSock = clients[sock];
	Packet * p = new Packet();
	// Loop forever
	int bytesRead;
	do {
		if (started) {
			// Allocate memory for a packet
			// Read message into packet struct
			ZeroMemory(p, sizeof(struct Packet));
			bytesRead = recv(currSock, (char*)p, sizeof(struct Packet) + 1, 0);
			if (bytesRead > 0) {
				std::cout << "Received " << bytesRead << " bytes from client id : " << currSock << "." << std::endl;
				//std::cout << "Player id:" << p.playerID << "Sends: " << p.message << std::endl;
				int sentBytes = 0;
				bool socketFailure = false;
				for (int i = 0; i < playerCount; ++i) {
					SOCKET outputSocket = clients[i];
					if (outputSocket != currSock) {
						int sentThisIteration = send(outputSocket, (char*)p, sizeof(struct Packet) + 1, 0);
						if (sentThisIteration > 0) {
							std::cout << "Socket thread: " << sock << "sent to" << i << std::endl;
						}
						else if (sentThisIteration == SOCKET_ERROR) {
							socketFailure = true;
							break;
						}
						else {
							std::cout << "Peer unexpectedly dropped connection" << std::endl;
							socketFailure = true;
							break;
						}
					}
				}
				if (socketFailure) {
					break;
				}
			}
			else if (bytesRead == SOCKET_ERROR) {
				std::cout << "scoket erro" << std::endl;
				playerCount--;
				break;
			}
			else {
				std::cout << "Peer unexpectedly dropped connection" << std::endl;
				playerCount--;
				break;
			}
		}
		else {
			bytesRead = -1;
		}
	} while (bytesRead != 0);
	std::cout << "Closing socket" << std::endl;
	shutdown(currSock, SD_SEND);
	closesocket(currSock);
}