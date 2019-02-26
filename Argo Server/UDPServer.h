#ifndef UDPSERVER_H
#define UDPSERVER_H

#include "Server.h"
#include <map>

struct ClientData {
	int index;
	sockaddr_in clientAddr;
};

//struct Lobby {
//	bool m_open = true;
//	bool m_inGame = false;
//	std::map<std::string, ClientData> m_clients;
//};

class UDPServer : public Server {
public:
	UDPServer();
	~UDPServer();
	/*std::vector<int> getAvailableLobbies();
	void createLobby();
	int mapToLobby();
	void startLobby(Lobby & lobby);

	void update();
	void sendToAllWaiting(Packet * p);
	void sendToAllInLobby(Packet * p, Lobby & lobby);*/

	bool createSock() override;
	bool bindSock() override;
	bool closeSock() override;

	void messageHandler();
private:
	sockaddr_in m_hint;
	bool m_started = false;
	//std::vector<Lobby> m_lobbies;
	std::map<std::string, ClientData> m_waiting;
};

#endif //!UDPSERVER_H