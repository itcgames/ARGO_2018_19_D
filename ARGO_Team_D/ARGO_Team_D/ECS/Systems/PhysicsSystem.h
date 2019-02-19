#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

// Inherits
#include "System.h"

// Includes
#include "../Components/Components.h"
#include "../Components/PositionComponent.h"
#include "../Components/BodyComponent.h"
#include "../Entities/Entity.h"
#include <Box2D/Box2D.h>

struct PhysicsComponents
{
	PositionComponent * position;
	BodyComponent * body;
};

/// <summary>
/// Physics System used to update positions of entities based on their Box2D bodies
/// </summary>
class PhysicsSystem : public System
{
public:
	PhysicsSystem(float worldScale);
	void addEntity(Entity * e) override;
	void update();
	void removeEntity(const int id) override;
private:
	float m_worldScale;
	std::map<int, PhysicsComponents> m_components;
};

#endif // !PHYSICSSYSTEM_H