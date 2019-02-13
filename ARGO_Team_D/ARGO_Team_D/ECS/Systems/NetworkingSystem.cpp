#include "NetworkingSystem.h"

NetworkingSystem::NetworkingSystem(Client * client)
{
	m_client = client;
}

void NetworkingSystem::update()
{
}

void NetworkingSystem::parseNetworkData(std::map<std::string, int> parsedMessage)
{
	for (auto const& pair : parsedMessage) {

		auto key = pair.first;
		auto value = pair.second;

		if (key == "ID") {
			m_client->setID(value);
		}
	}
}
