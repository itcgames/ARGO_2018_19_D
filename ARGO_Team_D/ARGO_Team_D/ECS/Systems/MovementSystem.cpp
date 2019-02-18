#include "MovementSystem.h"

MovementSystem::MovementSystem()
{
	allowedTypes.push_back("Position");
	allowedTypes.push_back("Velocity");
}

void MovementSystem::update()
{
	for (auto & comp : m_components) {
		auto & mov = comp.second;
		auto & v = mov.velocity;
		auto & p = mov.position;
		VectorAPI pos = VectorAPI(p->getPosition().x + (v->getVelocity().x), p->getPosition().y + (v->getVelocity().y));
		p->setPosition(pos);
	}
}

void MovementSystem::removeEntity(const int id)
{
	auto comp = m_components.find(id);
	if (comp != m_components.end()) {
		m_components.erase(comp);
	}
	m_entityList.erase(std::remove_if(m_entityList.begin(), m_entityList.end(), [id](Entity* en) {
		return en->id == id;
	}), m_entityList.end());
}
