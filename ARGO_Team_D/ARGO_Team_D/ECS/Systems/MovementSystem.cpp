#include "MovementSystem.h"

MovementSystem::MovementSystem()
{
	allowedTypes.push_back("Position");
	allowedTypes.push_back("Velocity");
}

void MovementSystem::update()
{
	for (Entity* i : m_entityList) {
		auto comps = i->getComponentsOfType(allowedTypes);
		PositionComponent * p = dynamic_cast<PositionComponent*>(comps["Position"]);
		
		VelocityComponent * v = dynamic_cast<VelocityComponent*>(comps["Velocity"]);

		VectorAPI pos = VectorAPI(p->getPosition().x + (v->getVelocity().x), p->getPosition().y + (v->getVelocity().y));
		p->setPosition(pos);
		
	}
	
}
