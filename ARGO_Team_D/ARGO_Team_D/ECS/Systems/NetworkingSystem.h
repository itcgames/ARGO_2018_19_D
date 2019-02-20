#ifndef NETWORKINSYSTEM_H
#define NETWORKINSYSTEM_H

#include "System.h"
#include "..//Client/Client.h"
#include <iostream>
#include "../Factories/PlayerFactory.h"

/// <summary>
/// Networking system controls positions of all entities.
/// </summary>
class NetworkingSystem : public System
{
public:
	NetworkingSystem();
	void initClientLocalClient(PlayerFactory * fact);
	void update();
	void updateFromHost();
	void updateClients();
	void sendToHost();
	void sendToClients();
	void parseNetworkData(std::map<std::string, int> parsedMessage);
	void parseNetworkDataStr(std::map<std::string, std::string> parsedMessage);
	bool getHost() { return m_client.getHost(); }
	Entity * m_player;
	std::vector<Entity*> m_clients;
	bool m_inLobby = false;
	bool m_inGame = false;
	PlayerFactory * m_playerFactory;
private:
	Client m_client;
};

#endif // !NETWORKINSYSTEM_H
