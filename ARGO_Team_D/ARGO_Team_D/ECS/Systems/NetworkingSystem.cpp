#include "NetworkingSystem.h"
#include "../ECS/Components/PositionComponent.h"
#include "../ECS/Components/NetworkComponent.h"

NetworkingSystem::NetworkingSystem()
{
}

void NetworkingSystem::initClientLocalClient(PlayerFactory * fact)
{
	if (m_client.init()) {
		std::cout << "Client Created" << std::endl;
	}
	else {
		std::cout << "Couldnt Connect Client                                                |" << std::endl;
		std::cout << "-----------------------------------------------------------------------" << std::endl;
	}

	m_playerFactory = fact;

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
	//std::cout << p->type << std::endl;
	if (!m_inGame) {
		if (p->type == MessageType::HOSTING) {
			std::cout << "You are the host" << std::endl;
			m_client.setHost(1);
			m_inLobby = true;
		}
		else if (p->type == MessageType::JOINED) {
			std::cout << "You are the client" << std::endl;
			m_clients.push_back(m_playerFactory->create(VectorAPI(0,0)));
			m_inLobby = true;
		}
		else if (p->type == MessageType::START) {
			std::cout << "starting game" << std::endl;
			m_inGame = true;
		}
	}
	else {
		switch (p->type)
		{
		case MessageType::PLAYER:
			std::cout << "Player" << std::endl;
			break;
		default:
			break;
		}

		std::vector<std::string> allowedTypes = { "Position", "Network" };
		if (m_client.getHost()) {
			auto comps = m_player->getComponentsOfType(allowedTypes);
			auto position = dynamic_cast<PositionComponent*>(comps["Position"]);
			Packet * p = new Packet();
			p->type = MessageType::PLAYER;
			p->position = position->getPosition();
			m_client.Send(p);
		}
		else {
		/*	for (auto & player : m_clients) {
				auto comps = player->getComponentsOfType(allowedTypes);
				auto position = dynamic_cast<PositionComponent*>(comps["Position"]);
				Packet * p = new Packet();
				p->type = MessageType::PLAYER;
				p->position = position->getPosition();
				m_client.Send(p);
			}*/
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
	/*for (auto & player : m_players) {

	}*/
}

void NetworkingSystem::sendToHost()
{
	//for (auto & player : m_players) {
	//	std::vector<std::string> allowedTypes = { "Position" , "Network"};
	//	auto comps = player->getComponentsOfType(allowedTypes);
	//	Packet * p = new Packet();
	//	p->position = dynamic_cast<PositionComponent*>(comps["Position"])->getPosition();
	//	p->type = MessageType::PLAYER;
	//	//  send own entity back
	//	m_client.Send(p);
	//}
}

void NetworkingSystem::sendToClients()
{
	//for (auto & player : m_players) {
	//	std::vector<std::string> allowedTypes = { "Position" };
	//	auto comps = player->getComponentsOfType(allowedTypes);
	//	Packet * p = new Packet();
	//	p->playerID = player->id;
	//	p->position = dynamic_cast<PositionComponent*>(comps["Position"])->getPosition();
	//	p->type = MessageType::PLAYER;
	//	//  send own entity back
	//	m_client.Send(p);
	//}
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
