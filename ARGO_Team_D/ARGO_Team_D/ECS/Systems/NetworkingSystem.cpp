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
			if (p->type == MessageType::LOBBYCREATED) {
				// Ignore duplicate lobbies
				int test1 = p->playerID;
				int test2 = m_lobbies.size() - 1;
				if (test1 > test2) {
					Lobby lb;
					lb.m_name = std::to_string(i + 1);
					lb.m_numPlayers = p->numOtherPlayers;
					if (lb.m_numPlayers <= 4) {
						m_lobbies.push_back(lb);
						m_lobbiesUpdated = true;
					}
				}
			}
			if (p->type == MessageType::LOBBYUPDATED) {
				if (p->playerID > m_lobbies.size()) {
					Lobby lb;
					lb.m_name = i;
					lb.m_numPlayers = p->numOtherPlayers;
					if (lb.m_numPlayers <= 4) {
						m_lobbies.push_back(lb);
						m_lobbiesUpdated = true;
					}
				}
				auto & lobby = m_lobbies.at(p->playerID);
				lobby.m_numPlayers = p->numOtherPlayers;
				m_lobbiesUpdated = true;
			}
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
}

void NetworkingSystem::readyUp()
{
	Packet * p = new Packet();
	ZeroMemory(p, sizeof(struct Packet));
	p->type = MessageType::READY;
	m_client->Send(p);
}

void NetworkingSystem::unready()
{
	Packet * p = new Packet();
	ZeroMemory(p, sizeof(struct Packet));
	p->type = MessageType::UNREADY;
	m_client->Send(p);
	auto test = m_client->Receive();
}

std::vector<NetworkingSystem::Lobby>& NetworkingSystem::getLobbies()
{
	// TODO: insert return statement here
	return m_lobbies;
}

bool NetworkingSystem::createNewLobby()
{
	if (m_lobbies.size() < MAX_LOBBIES && !m_inLobby) {
		Lobby lb;
		m_lobbies.push_back(lb);
		auto & lobby = m_lobbies.back();
		lobby.m_name = std::to_string(m_lobbies.size());
		lobby.m_numPlayers = 1;
		m_inLobby = true;
		m_client->setHost(1);
		m_lobbyInNumber = m_lobbies.size() - 1;
	}
	else {
		return false;
	}
	Packet * p = new Packet();
	ZeroMemory(p, sizeof(struct Packet));
	p->type = MessageType::LOBBYCREATED;
	m_client->Send(p);
	return true;
}

void NetworkingSystem::startLobby()
{
	if (m_inLobby && m_client->getHost()) {
		Packet * p = new Packet();
		ZeroMemory(p, sizeof(struct Packet));
		p->type = MessageType::START;
		m_client->Send(p);
	}
}

bool NetworkingSystem::leaveLobby()
{
	if (m_inLobby) {
		if (m_client->getHost()) {
			m_lobbies.erase(m_lobbies.begin() + m_lobbyInNumber);
		}
		Packet * p = new Packet();
		ZeroMemory(p, sizeof(struct Packet));
		p->type = MessageType::LEAVELOBBY;
		m_client->Send(p);
		m_client->setHost(0);
		m_inLobby = false;
		return true;
	}
	return false;
}

int NetworkingSystem::getMyLobby()
{
	return m_lobbyInNumber;
}

bool NetworkingSystem::joinLobby()
{
	if (!m_inLobby) {
		Packet * p = new Packet();
		ZeroMemory(p, sizeof(struct Packet));
		p->type = MessageType::JOINLOBBY;
		m_client->Send(p);
		return true;
	}
	return false;
}
