#include "Server.h"
#include <iostream>
using namespace std;

Server::Server()
{
	m_numPlayers = 0;
	m_clients.resize(MAX_CLIENTS);
	m_clientAddrs.resize(MAX_CLIENTS);
}

Server::~Server()
{
}

bool Server::winSockInit()
{
	m_version = MAKEWORD(2, 2);

	int wsOk = WSAStartup(m_version, &m_data);
	if (wsOk != 0)
	{
		cerr << "Can't Initialize winsock! Quitting" << endl;
		exit(EXIT_FAILURE);
		return false;
	}
	cout << "Winsock started" << std::endl;
	return true;
}
