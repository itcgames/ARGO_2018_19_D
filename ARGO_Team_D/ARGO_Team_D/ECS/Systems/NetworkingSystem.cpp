#include "NetworkingSystem.h"

NetworkingSystem::NetworkingSystem()
{
}

void NetworkingSystem::initClientLocalClient()
{
	m_client = new UDPClient();
	if (m_client->init()) {
		std::cout << "Client Created" << std::endl;
	/*	Packet p;
		p.type = MessageType::JOINED;
		m_client->Send(&p);
		auto test = m_client->Receive();
		std::cout << std::endl;*/
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
	n.body = dynamic_cast<BodyComponent*>(comps["Body"]);
	m_components.insert(std::make_pair(e->id, n));
	m_entityList.push_back(e);
}

void NetworkingSystem::update()
{
	if (m_client != nullptr) {
		for (int i = 0; i < m_components.size() - 1; ++i) {
			Packet * p = m_client->Receive();
			if (p->type == MessageType::START && !m_inGame) {
				std::cout << "Started%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
				m_localPlayerID = p->playerID;
				int numPlayers = p->numOtherPlayers + 1;
				std::vector<int> playerIDs;
				for (int i = 0; i < numPlayers; ++i) {
					playerIDs.push_back(i);
				}
				// Set local player
				for (auto & entityComps : m_components) {
					int entityID = entityComps.first;
					auto & networkingComps = entityComps.second;
					if (networkingComps.network != nullptr && networkingComps.network->networkID == -1) {
						networkingComps.network->networkID = m_localPlayerID;
						break;
					}
				}
				playerIDs.erase(std::remove(playerIDs.begin(), playerIDs.end(), m_localPlayerID));
				// Set online players
				for (int i = 0; i < playerIDs.size(); ++i) {
					for (auto & entityComps : m_components) {
						int entityID = entityComps.first;
						auto & networkingComps = entityComps.second;
						if (networkingComps.network != nullptr && networkingComps.network->networkID == -1) {
							networkingComps.network->networkID = playerIDs[i];
							break;
						}
					}
				}
				m_inGame = true;
			}
			if (p->type == MessageType::PLAYER) {
				for (auto & entityComps : m_components) {
					int entityID = entityComps.first;
					auto & networkingComps = entityComps.second;
					if (networkingComps.network != nullptr && networkingComps.network->networkID == p->playerID) {
						//std::cout << "Received from " << p->playerID << std::endl;
						auto & pos = networkingComps.position;
						//std::cout << p->position.x << ", " << p->position.y << std::endl;
						pos->setPosition(p->position);
						/*auto & body = networkingComps.body;
						body->setPosition(b2Vec2(p->position.x / 30.f, p->position.y / 30.f));*/
					}
				}
			}
		}
		if (m_inGame) {
			std::cout << "Update" << std::endl;
			for (auto & entityComps : m_components) {
				Packet * p = new Packet();
				int entityID = entityComps.first;
				auto & networkingComps = entityComps.second;
				if (networkingComps.network->networkID == m_localPlayerID) {
					std::cout << "Sending for Local" << std::endl;
					p->playerID = m_localPlayerID;
					p->type = MessageType::PLAYER;
					p->position = networkingComps.position->getPosition();
					m_client->Send(p);
				}
			}
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

void NetworkingSystem::joinServer()
{
	Packet * p = new Packet();
	ZeroMemory(p, sizeof(struct Packet));
	p->type = MessageType::JOINED;
	m_client->Send(p);
	auto test = m_client->Receive();
}