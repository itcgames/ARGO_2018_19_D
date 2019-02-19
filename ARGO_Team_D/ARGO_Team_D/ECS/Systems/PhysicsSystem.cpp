#include "PhysicsSystem.h"

/// <summary>
/// Constructor for the physics system
/// </summary>
/// <param name="worldScale">The Box2D world scale</param>
PhysicsSystem::PhysicsSystem(float worldScale) : m_worldScale(worldScale) 
{
}

/// <summary>
/// Override the addEntity() method
/// </summary>
/// <param name="e">Entity to be added</param>
void PhysicsSystem::addEntity(Entity * e)
{
	std::vector<std::string> allowedTypes{ "Position", "Body" };
	auto comps = e->getComponentsOfType(allowedTypes);
	if (comps.size() == allowedTypes.size())
	{
		PhysicsComponents c;
		c.position = dynamic_cast<PositionComponent*>(comps["Position"]);
		c.body = dynamic_cast<BodyComponent*>(comps["Body"]);
		m_components.insert(std::make_pair(e->id, c));
		m_entityList.push_back(e);
	}
}

/// <summary>
/// Update used to update the position of enetities based on Box2D 
/// physics that have already been calculated
/// </summary>
void PhysicsSystem::update()
{
	for (auto & comp : m_components)
	{
		auto & pc = comp.second;
		PositionComponent * p = pc.position;
		BodyComponent * b = pc.body;
		VectorAPI currentPos = p->getPosition();
		b2Body * body = b->getBody();
		b2Vec2 bodyPos = body->GetPosition();
		VectorAPI dimensions = b->getDimensions();
		currentPos.x = bodyPos.x;
		currentPos.y = bodyPos.y;
		p->setX(currentPos.x * m_worldScale - (dimensions.x / 2.f));
		p->setY(currentPos.y * m_worldScale - (dimensions.y / 2.f));
	}
}

void PhysicsSystem::removeEntity(const int id)
{
	auto comp = m_components.find(id);
	if (comp != m_components.end()) {
		m_components.erase(comp);
	}
	m_entityList.erase(std::remove_if(m_entityList.begin(), m_entityList.end(), [id](Entity* en) {
		return en->id == id;
	}), m_entityList.end());
}
