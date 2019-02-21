#include "TCPServer.h"
#include <iostream>
#include <thread>
#include "../ARGO_TEAM_D/ARGO_TEAM_D/Utils/Packet.h"
#include <string>

TCPServer::TCPServer()
{
	m_started = false;
}

TCPServer::~TCPServer()
{
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
		std::cerr << "Cannot bin sock: " << WSAGetLastError() << std::endl;
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
	while (m_numPlayers <= MAX_CLIENTS) {
		if (m_numPlayers != MAX_CLIENTS) {
			m_clients[m_numPlayers] = accept(m_listening, &m_clientAddrs[m_numPlayers], &addrSize);
			if (m_clients[m_numPlayers] != INVALID_SOCKET) {
				ZeroMemory(p, sizeof(struct Packet));
				p->playerID = m_numPlayers;
				p->type = m_numPlayers == 0 ? MessageType::HOSTING : MessageType::JOINED;

				std::thread t([&](TCPServer * serv) {
					serv->messageHandler(m_numPlayers, m_numPlayers, m_clients);
				}, this);

				send(m_clients[m_numPlayers], (char*)p, sizeof(struct Packet) + 1, 0);

				m_numPlayers++;
				std::cout << "Num players: " << m_numPlayers << std::endl;
				t.detach();
			}
		}
		else if (!m_started) {
			ZeroMemory(p, sizeof(struct Packet));
			p->playerID = m_numPlayers + 1;
			p->type = MessageType::START;
			for (auto & client : m_clients) {
				int sent = send(client, (char*)p, sizeof(struct Packet) + 1, 0);
				if (sent <= 0)
					break;
			}
			m_started = true;
			std::cout << "Server sends start" << std::endl;
		}
	}
}

void TCPServer::messageHandler(SOCKET sock, int & playerCount, SOCKET * clients)
{
	SOCKET currSock = clients[sock];
	Packet * p = new Packet();
	// Loop forever
	int bytesRead;
	do {
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
	} while (bytesRead != 0);
	std::cout << "Closing socket" << std::endl;
	shutdown(currSock, SD_SEND);
	closesocket(currSock);
}