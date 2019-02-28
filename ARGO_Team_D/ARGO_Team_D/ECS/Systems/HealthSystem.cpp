#include "HealthSystem.h"

HealthSystem::HealthSystem() : m_playerAlive(true)
{
}

HealthSystem::~HealthSystem()
{
}

void HealthSystem::addEntity(Entity * e)
{
	std::vector<std::string> allowedTypes{ "Body" , "Health" };
	auto comps = e->getComponentsOfType(allowedTypes);
	if (comps.size() >= allowedTypes.size() - 1)
	{
		HealthComponents c;
		c.body = dynamic_cast<BodyComponent*>(comps["Body"]);
		c.health = dynamic_cast<HealthComponent*>(comps["Health"]);
		m_components.insert(std::make_pair(e->id, c));
		m_entityList.push_back(e);
	}
}

void HealthSystem::update()
{
	for (auto & comp : m_components)
	{
		auto & hc = comp.second;
		int hitCount = hc.body->getBulletHitCount();
		int currentHealth = hc.health->getHealth();
		if (hitCount > 0)
		{
			hc.body->setBulletHitCount(0);
			currentHealth -= (hitCount * 10);
		}
		if (hc.body->getBody()->GetPosition().y > 180)
		{
			currentHealth = 0;
		}
		if (currentHealth > 0)
		{
			hc.health->setHealth(currentHealth);
		}
		else
		{
			hc.health->setHealth(100);
			int currentLives = hc.health->getLives() - 1;
			hc.health->setLives(currentLives == 0 ? 3 : currentLives);
			hc.body->resetPos();
			if (currentLives == 0)
			{
				m_playerAlive = false;
			}
		}
	}
}

void HealthSystem::removeEntity(const int id)
{
	auto comp = m_components.find(id);
	if (comp != m_components.end()) {
		m_components.erase(comp);
	}
	m_entityList.erase(std::remove_if(m_entityList.begin(), m_entityList.end(), [id](Entity* en) {
		return en->id == id;
	}), m_entityList.end());
}

bool HealthSystem::playerAlive()
{
	return m_playerAlive;
}

void HealthSystem::setPlayerAliveStatus(bool status)
{
	m_playerAlive = status;
}

void HealthSystem::reset()
{
	for (auto & comp : m_components)
	{
		auto & hc = comp.second;
		hc.health->setHealth(100);
		hc.health->setLives(3);
	}
}
