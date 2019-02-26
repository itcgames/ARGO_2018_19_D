#include "UDPServer.h"
#include <iostream>

UDPServer::UDPServer()
{
}

UDPServer::~UDPServer()
{
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
			char clientIP[256];
			ZeroMemory(&clientIP, 256);
			// Get the client ip
			inet_ntop(addrFamily, &clientAddr.sin_addr, clientIP, 256);
			


			// Check if IP exisits in waiting
			if (p.type == MessageType::JOINED) {
				ClientData data;
				data.index = numWaiting;
				data.clientAddr = clientAddr;
				m_waiting[clientIP] = data;
				numWaiting++;
				if (numWaiting >= MAX_CLIENTS) {
					Packet * startMsg = new Packet();
					for (auto & ip : m_waiting) {
						ZeroMemory(startMsg, sizeof(struct Packet));
						startMsg->type = MessageType::START;
						int sendResult = sendto(m_listening, (char*)&startMsg, sizeof(struct Packet) + 1, 0, (LPSOCKADDR)&m_waiting[ip.first].clientAddr, sizeof(m_waiting[ip.first].clientAddr));
						if (sendResult == SOCKET_ERROR) {
							std::cerr << "Failed to send: " << WSAGetLastError() << std::endl;
						}
						else {
							char ipSentTo[256];
							ZeroMemory(&ipSentTo, 256);
							inet_ntop(AF_INET, &clientAddr.sin_addr, ipSentTo, 256);
							std::cout << "Sent message to :" << ipSentTo << std::endl;
						}
					}
				}
			}

			for (int i = 0; i < numWaiting; ++i) {
				//Send to everyone but yourself
				if (i != m_waiting[clientIP].index) {
					int sendResult = sendto(m_listening, (char*)&p, sizeof(struct Packet) + 1, 0, (LPSOCKADDR)&m_waiting[clientIP].clientAddr, sizeof(m_waiting[clientIP].clientAddr));
					if (sendResult != SOCKET_ERROR) {
						std::cerr << "Failed to send: " << WSAGetLastError() << std::endl;
					}
					else {
						char ipSentTo[256];
						ZeroMemory(&ipSentTo, 256);
						inet_ntop(AF_INET, &clientAddr.sin_addr, ipSentTo, 256);
						std::cout << "Sent message to :" << ipSentTo << std::endl;
					}
				}
			}

			std::cout << "Received message from " << clientIP << std::endl;
		}
	}
}
