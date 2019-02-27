#ifndef NETWORKINSYSTEM_H
#define NETWORKINSYSTEM_H

#include "System.h"
#include "..//Client/UDPClient.h"
#include "../Components/PositionComponent.h"
#include "../Components/NetworkComponent.h"
#include "../Components/BodyComponent.h"

#include <iostream>

struct NetworkingComponents {
	PositionComponent * position = nullptr;
	NetworkComponent * network = nullptr;
	BodyComponent * body = nullptr;
};

/// <summary>
/// Networking system controls positions of all entities.
/// </summary>
class NetworkingSystem : public System
{
public:
	NetworkingSystem();
	void initClientLocalClient();
	void addEntity(Entity * e) override;
	void update();
	void removeEntity(const int id) override;
	bool m_inGame = false;
	void joinServer();
	void readyUp();
	void unready();
private:
	Entity * m_player;
	std::vector<Entity*> * m_clients;
	UDPClient * m_client;
	std::map<int, NetworkingComponents> m_components;
	std::vector<std::string> m_allowedTypes = { "Network", "Position", "Body"};
	bool m_inLobby = false;
	int hostEntity = 0;
	int m_localPlayerID = -1;
};

#endif // !NETWORKINSYSTEM_H
