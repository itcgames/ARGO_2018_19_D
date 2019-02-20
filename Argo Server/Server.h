#ifndef SERVER_H
#define SERVER_H

#pragma comment (lib, "ws2_32.lib")
#include <WS2tcpip.h>

#define MAX_CLIENTS 2


class Server {
public:
	Server();
	~Server();

	bool winSockInit();

	virtual bool createSock() = 0;
	virtual bool bindSock() = 0;
	virtual bool closeSock() = 0;
protected:
	bool m_running;
	WSADATA m_data;
	WORD m_version;
	SOCKET m_listening;
	SOCKET m_clients[MAX_CLIENTS];
	sockaddr m_clientAddrs[MAX_CLIENTS];
	int m_numPlayers;
	const int port = 8080;
};

#endif // !SERVER_h