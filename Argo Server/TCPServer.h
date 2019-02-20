#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "Server.h"
#include <map>
#include <thread>

class TCPServer : public Server {
public:
	TCPServer();
	~TCPServer();

	bool createSock() override;
	bool bindSock() override;
	bool closeSock() override;

	void acceptConnections();
	static void messageHandler(SOCKET sock, int & playerCount, SOCKET * clients);
private:
	sockaddr_in m_hint;
	bool m_started = false;
};
#endif // !TCPSERVER_H
