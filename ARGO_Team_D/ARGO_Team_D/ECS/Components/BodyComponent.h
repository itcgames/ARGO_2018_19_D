#ifndef BODYCOMPONENT_H
#define BODYCOMPONENT_H

// Inherits
#include "Components.h"

// Includes
#include <Box2D/Box2D.h>
#include "..\Utils\VectorAPI.h"
#include "../Level/Level.h"

/// <summary>
/// Box2D Body Component
/// </summary>
class BodyComponent : public Component {
public:
	// Public Functions
	BodyComponent(float x, float y, float w, float h, b2World & world, float worldScale);
	BodyComponent(float x, float y, float rad, b2World & world, float worldScale);
	~BodyComponent();
	b2Body * getBody();
	bool isCircle();
	VectorAPI getDimensions();
	bool isOnGround();
	void groundContactStart();
	void groundContactEnd();

private:
	// Private Functions
	void init(float x, float y, float w, float h);

	// Private Members

	// Box2D world
	b2World & m_refWorld;
	float m_worldScale;

	// Physics Body
	bool m_isCircle;
	b2Body * m_body;
	b2BodyDef m_bodyDef;
	b2Shape * m_shape;
	b2FixtureDef m_fixtureDef;
	VectorAPI m_dimensions;

	// Sensor Body
	b2PolygonShape * m_groundSensorShape;
	b2FixtureDef m_groundFixtureDef;
	bool m_onGround;
	CollisionData m_data;
};

#endif // !BODYCOMPONENT_H
