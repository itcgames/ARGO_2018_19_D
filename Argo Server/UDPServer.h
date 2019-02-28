#ifndef UDPSERVER_H
#define UDPSERVER_H

#include "Server.h"
#include <map>

struct ClientData {
	int index;
	sockaddr_in clientAddr;
	int clientAddrLen;
	std::string mapping;
};

class UDPServer : public Server {
public:
	struct Lobby {
		bool m_open = true;
		bool m_inGame = false;
		std::map<std::string, ClientData> m_clients;
	};

	UDPServer();
	~UDPServer();
	std::vector<int> getAvailableLobbies();
	bool createLobby();
	int mapToLobby();
	void startLobby(Lobby & lobby);
	void handleLobby(Lobby & lobby, ClientData & current, Packet & p);
	void mapClientToLobby(ClientData & current);
	void updateLobbyInfo(Packet & p);
	void removeFromLobby(std::string & mapping);

	bool createSock() override;
	bool bindSock() override;
	bool closeSock() override;

	void messageHandler();
private:
	sockaddr_in m_hint;
	bool m_started = false;
	std::vector<Lobby> m_lobbies;
	std::map<std::string, ClientData> m_waiting;
	std::map<std::string, int> m_ipToLobby;
};

#endif //!UDPSERVER_H