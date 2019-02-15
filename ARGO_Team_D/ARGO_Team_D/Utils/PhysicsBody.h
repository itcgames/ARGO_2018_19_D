#ifndef PHYSICSBODY_H
#define PHYSICSBODY_H

#include <Box2D/Box2D.h>
#include "CollisionData.h"

struct PhysicsBody {
	PhysicsBody(std::string name) : data(name, this) {};
	b2BodyDef bodyDef;
	b2Body * body = nullptr;
	b2PolygonShape shape;
	b2FixtureDef fixture;
	CollisionData data;
};

#endif //!PHYSICSBODY_H