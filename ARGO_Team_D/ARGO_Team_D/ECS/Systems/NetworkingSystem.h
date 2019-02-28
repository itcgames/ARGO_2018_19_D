#ifndef NETWORKINSYSTEM_H
#define NETWORKINSYSTEM_H

#include "System.h"
#include "..//Client/UDPClient.h"
#include "../Components/PositionComponent.h"
#include "../Components/NetworkComponent.h"
#include "../Components/BodyComponent.h"

#include <iostream>

#define MAX_LOBBIES 5

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
	struct Lobby {
		std::string m_name;
		int m_numPlayers = 0;
		bool m_open;
	};
	NetworkingSystem();
	void initClientLocalClient();
	void addEntity(Entity * e) override;
	void update();
	void removeEntity(const int id) override;
	bool m_inGame = false;
	void joinServer();
	void readyUp();
	void unready();
	std::vector<Lobby> & getLobbies();
	bool createNewLobby();
	void startLobby();
	bool leaveLobby();
	int getMyLobby();
	bool joinLobby();
	bool m_inGameChecked = false;
	bool m_lobbiesUpdated = false;
private:
	Entity * m_player;
	std::vector<Entity*> * m_clients;
	UDPClient * m_client;
	std::map<int, NetworkingComponents> m_components;
	std::vector<std::string> m_allowedTypes = { "Network", "Position", "Body"};
	bool m_inLobby = false;
	int hostEntity = 0;
	int m_localPlayerID = -1;
	int m_lobbyInNumber = -1;
	std::vector<NetworkingSystem::Lobby> m_lobbies;
};

#endif // !NETWORKINSYSTEM_H
