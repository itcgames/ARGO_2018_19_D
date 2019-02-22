#include "NetworkingSystem.h"

NetworkingSystem::NetworkingSystem()
{
}

void NetworkingSystem::initClientLocalClient()
{
	std::string ipAddress = "149.153.106.150";			// IP Address of the server
	int port = 8080;

	if (m_client.init(ipAddress, port)) {
		std::cout << "Client Created" << std::endl;
	}
	else {
		std::cout << "Couldnt Connect Client                                                |" << std::endl;
		std::cout << "-----------------------------------------------------------------------" << std::endl;
	}
}

void NetworkingSystem::addEntity(Entity * e)
{
	auto comps = e->getComponentsOfType(m_allowedTypes);
	NetworkingComponents n;
	n.position = dynamic_cast<PositionComponent*>(comps["Position"]);
	n.network = dynamic_cast<NetworkComponent*>(comps["Network"]);
	m_components.insert(std::make_pair(e->id, n));
	m_entityList.push_back(e);
}

void NetworkingSystem::update()
{
	for (int i = 0; i < m_components.size() - 1; ++i) {
		Packet * p = m_client.Receive();
			if (p->type == MessageType::JOINED || p->type == MessageType::HOSTING) {
				std::cout << "Player joined" << p->playerID << std::endl;
				for (int i = 0; i < p->numOtherPlayers + 1; ++i) {
					for (auto & entityComps : m_components) {
						int entityID = entityComps.first;
						auto & networkingComps = entityComps.second;

						if (networkingComps.network->networkID == -1) {
							if (m_localPlayerID == -1) {
								m_localPlayerID = p->playerID;
							}
							networkingComps.network->networkID = p->playerID;
							break;
						}
					}
				}
			}
			if (p->type == MessageType::PLAYER) {
				for (auto & entityComps : m_components) {
					int entityID = entityComps.first;
					auto & networkingComps = entityComps.second;
					if (networkingComps.network != nullptr && networkingComps.network->networkID == p->playerID) {
						std::cout << "Received from " << p->playerID << std::endl;
						auto & pos = networkingComps.position;
						std::cout << p->position.x << ", " << p->position.y << std::endl;
						pos->setPosition(p->position);
					}
				}
			}
	}
	std::cout << "Update" << std::endl;
	for (auto & entityComps : m_components) {
		Packet * p = new Packet();
		int entityID = entityComps.first;
		auto & networkingComps = entityComps.second;
		if (networkingComps.network->networkID == m_localPlayerID) {
			std::cout << "Sending for Local" << std::endl;
			p->type = MessageType::PLAYER;
			p->position = networkingComps.position->getPosition();
			m_client.Send(p);
		}
	}
}

void NetworkingSystem::removeEntity(const int id)
{
	auto comp = m_components.find(id);
	if (comp != m_components.end()) {
		m_components.erase(comp);
	}
	m_entityList.erase(std::remove_if(m_entityList.begin(), m_entityList.end(), [id](Entity* en) {
		return en->id == id;
	}), m_entityList.end());
}