#include "UDPClient.h"
#include <iostream>

UDPClient::UDPClient()
{
}

UDPClient::~UDPClient()
{
}

bool UDPClient::init()
{
	int addrFamily = AF_INET;
	m_hint.sin_family = AF_INET;
	m_hint.sin_port = htons(8080);
	inet_pton(addrFamily, "149.153.106.150", &m_hint.sin_addr);
	m_sock = socket(addrFamily, SOCK_DGRAM, 0);

	if (m_sock == INVALID_SOCKET) {
		std::cerr << "Error creating socket" << WSAGetLastError() << std::endl;
		return false;
	}
	else {
		//Make non blocking
		unsigned long iMode = 1;
		int result = ioctlsocket(m_sock, FIONBIO, &iMode);
		if (result != NO_ERROR) {
			std::cerr << "Socket failed with error" << result << std::endl;
			return false;
		}
	}
	return true;
}

bool UDPClient::Send(Packet * p)
{
	int result = sendto(m_sock, (char*)p, sizeof(struct Packet) + 1, 0, (LPSOCKADDR)&m_hint, sizeof(m_hint));
	if (result == SOCKET_ERROR) {
		std::cerr << "Socket sen failed with " << WSAGetLastError() << std::endl;
		return false;
	}
	return true;
}

Packet * UDPClient::Receive()
{
	Packet * p = new Packet();
	ZeroMemory(p, sizeof(struct Packet));
	int size = sizeof(m_hint);
	int bytesRecv = recvfrom(m_sock, (char*)p, sizeof(struct Packet) + 1, 0, (LPSOCKADDR)&m_hint, &size);
	if (bytesRecv == SOCKET_ERROR) {
		if (WSAGetLastError() != WSAEWOULDBLOCK) {
			std::cerr << "Error receiving: " << WSAGetLastError() << std::endl;
		}
	}
	return p;
}
