#include "Client.h"
#include "ParseUtils.h"
#include <iostream>

Client::Client()
{
	m_packet = new Packet();
}

Client::~Client()
{
}

bool Client::init()
{
	std::string ip = "192.168.1.9";
	int port = 8080;

	m_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (m_sock == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket, Err #" << WSAGetLastError() << std::endl;
		WSACleanup();
		return false;
	}

	u_long iMode = 1;
	int result = ioctlsocket(m_sock, FIONBIO, &iMode);
	if (result != NO_ERROR) {
		std::cout << "ioctlsocket failed with error: " << result << std::endl;
		return false;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(m_sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		std::cout << "-----------------------------------------------------------------------" << std::endl;
		std::cerr << "Can't create socket, Err #" << WSAGetLastError() << std::endl; 
		std::cout << "Non fatal error apparently just gonna use the the socket anyway :/    |" << std::endl;
		std::cout << "vvvvv Dont mind this vvvvv                                            |" << std::endl;
		return false;
	}
	return true;
}

bool Client::Send(Packet * p)
{
	auto size = sizeof(struct Packet) + 1;
	int sendResult = send(m_sock, (char*)p, size, 0);
	if (sendResult == SOCKET_ERROR) {
		return false;
	}
}

Packet * Client::Receive()
{
	ZeroMemory(m_packet, sizeof(struct Packet));
	int bytesReceived = recv(m_sock, (char*)m_packet, sizeof(struct Packet), 0);
	if (bytesReceived == SOCKET_ERROR) {
		int error = WSAGetLastError();
		if (error != WSAEWOULDBLOCK) {
			std::cout << WSAGetLastError() << std::endl;
		}
	}
	return m_packet;
}

void Client::close()
{
	closesocket(m_sock);
	WSACleanup();
}