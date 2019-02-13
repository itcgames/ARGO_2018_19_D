#ifndef NETWORKINSYSTEM_H
#define NETWORKINSYSTEM_H

#include "System.h"
#include "..//Client/Client.h"

/// <summary>
/// Networking system controls positions of all entities.
/// </summary>
class NetworkingSystem : public System
{
public:
	NetworkingSystem() {};
	NetworkingSystem(Client * client);
	void update();
	void parseNetworkData(std::map<std::string, int> parsedMessage);

private:
	Client * m_client;
};

#endif // !NETWORKINSYSTEM_H
