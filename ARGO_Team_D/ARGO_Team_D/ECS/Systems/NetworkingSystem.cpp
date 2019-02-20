#include "NetworkingSystem.h"
#include "../ECS/Components/PositionComponent.h"
#include "../ECS/Components/NetworkComponent.h"

NetworkingSystem::NetworkingSystem()
{
}

void NetworkingSystem::initClientLocalClient()
{
	if (m_client.init()) {
		std::cout << "Client Created" << std::endl;
	}
	else {
		std::cout << "Couldnt Connect Client                                                |" << std::endl;
		std::cout << "-----------------------------------------------------------------------" << std::endl;
	}

	////parseNetworkData(m_client.processMessage(m_client.Receive()));
	//auto p = m_client.Receive();
	//switch (p->type)
	//{
	//case MessageType::HOSTING:
	//	std::cout << "Hosting at : " << p->playerID << std::endl;
	//	m_client.setHost(1);
	//	break;
	//case MessageType::JOINED:
	//	std::cout << "Player Joined id is: " << p->playerID << std::endl;
	//	break;
	//default:
	//	break;
	//}
}

void NetworkingSystem::update()
{
	Packet * p = m_client.Receive();
	if (p->type == MessageType::HOSTING) {
		m_client.setHost(1);
		m_inLobby = true;
	}
	else if (p->type == MessageType::JOINED) {
		m_inLobby = true;
	}
	else if (p->type == MessageType::START) {
		m_inGame = true;
	}
	if (m_inGame) {
		switch (p->type)
		{
		case MessageType::PLAYER:
			std::cout << "Player" << std::endl;
			break;
		default:
			break;
		}
	}
}

void NetworkingSystem::updateFromHost()
{
	// Update everything from here
	//parseNetworkDataStr(m_client.processMessageStr(m_client.Receive()));
	auto p = m_client.Receive();
}

void NetworkingSystem::updateClients()
{
	// Update client entities from here
	//parseNetworkDataStr(m_client.processMessageStr(m_client.Receive()));
	auto p = m_client.Receive();
	for (auto & player : m_players) {

	}
}

void NetworkingSystem::sendToHost()
{
	for (auto & player : m_players) {
		std::vector<std::string> allowedTypes = { "Position" , "Network"};
		auto comps = player->getComponentsOfType(allowedTypes);
		Packet * p = new Packet();
		p->position = dynamic_cast<PositionComponent*>(comps["Position"])->getPosition();
		p->type = MessageType::PLAYER;
		//  send own entity back
		m_client.Send(p);
	}
}

void NetworkingSystem::sendToClients()
{
	for (auto & player : m_players) {
		std::vector<std::string> allowedTypes = { "Position" };
		auto comps = player->getComponentsOfType(allowedTypes);
		Packet * p = new Packet();
		p->playerID = player->id;
		p->position = dynamic_cast<PositionComponent*>(comps["Position"])->getPosition();
		p->type = MessageType::PLAYER;
		//  send own entity back
		m_client.Send(p);
	}
}

void NetworkingSystem::parseNetworkData(std::map<std::string, int> parsedMessage)
{
	/*for (auto const& pair : parsedMessage) {

		auto key = pair.first;
		auto value = pair.second;

		if (key == "ID") {
			m_client.setID(value);
		}

		if (key == "Host") {
			m_client.setHost(value);
		}
	}*/

}

void NetworkingSystem::parseNetworkDataStr(std::map<std::string, std::string> parsedMessage)
{
	for (auto const& pair : parsedMessage) {

		auto key = pair.first;
		auto value = pair.second;

		if (key == "HostSays") {
			cout << "Host Says: " << value << endl;
		}


		if (key == "ClientSays") {
			cout << "Client Says: " << value << endl;
		}
	}
}
