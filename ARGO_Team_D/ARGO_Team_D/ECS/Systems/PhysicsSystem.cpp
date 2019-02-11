#include "PhysicsSystem.h"

/// <summary>
/// Constructor for the physics system
/// </summary>
/// <param name="worldScale">The Box2D world scale</param>
PhysicsSystem::PhysicsSystem(float worldScale) : m_worldScale(worldScale) 
{
}

/// <summary>
/// Update used to update the position of enetities based on Box2D 
/// physics that have already been calculated
/// </summary>
void PhysicsSystem::update()
{
	std::vector<std::string> allowedTypes{ "Position", "Body" };
	for (Entity* i : m_entityList) {
		auto comps = i->getComponentsOfType(allowedTypes);
		if (comps.size() == allowedTypes.size()) {
			PositionComponent * p = dynamic_cast<PositionComponent*>(comps["Position"]);
			BodyComponent * b = dynamic_cast<BodyComponent*>(comps["Body"]);
			VectorAPI currentPos = p->getPosition();
			b2Body * body = b->getBody();
			b2Vec2 bodyPos = body->GetPosition();
			VectorAPI dimensions = b->getDimesnions();
			currentPos.x = bodyPos.x ;
			currentPos.y = bodyPos.y;
			p->setX(currentPos.x * m_worldScale - (dimensions.x / 2.f));
			p->setY(currentPos.y * m_worldScale - (dimensions.y / 2.f));
		}
	}
}