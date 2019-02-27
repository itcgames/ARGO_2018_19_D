#ifndef SERVER_H
#define SERVER_H

#pragma comment (lib, "ws2_32.lib")
#include <WS2tcpip.h>
#include <vector>
#include "../ARGO_Team_D/ARGO_Team_D/Utils/Packet.h"

#define MAX_CLIENTS 2
#define MAX_LOBBIES 5

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
	
	std::vector<SOCKET> m_clients;
	std::vector<sockaddr> m_clientAddrs;
	int m_numPlayers;
	const int port = 8080;
};

#endif // !SERVER_h