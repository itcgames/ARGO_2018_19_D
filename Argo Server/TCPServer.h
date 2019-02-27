#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "Server.h"
#include <map>
#include <thread>
#include <vector>

class TCPServer : public Server {
public:
	struct Lobby {
		bool m_open = true;
		bool m_inGame = false;
		std::vector<SOCKET> m_clients;
	};
	TCPServer();
	~TCPServer();
	std::vector<int> getAvailableLobbies();
	void createLobby();
	int mapToLobby();
	void startLobby(Lobby & lobby);

	void update();
	void sendToAllWaiting(Packet * p);
	void sendToAllInLobby(Packet * p, Lobby & lobby);

	bool createSock() override;
	bool bindSock() override;
	bool closeSock() override;

	void acceptConnections();
	static void messageHandler(SOCKET sock, int playerCount, std::vector<SOCKET> &clients, bool & started);
private:
	sockaddr_in m_hint;
	bool m_started = false;
	std::vector<Lobby> m_lobbies;
};
#endif // !TCPSERVER_H
