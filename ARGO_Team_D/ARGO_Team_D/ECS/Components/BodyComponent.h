#ifndef BODYCOMPONENT_H
#define BODYCOMPONENT_H

// Inherits
#include "Components.h"

// Includes
#include <string>
#include <Box2D/Box2D.h>
#include "..\Utils\VectorAPI.h"
#include "..\Utils\CollisionData.h"

// Debug
#include <iostream>

/// <summary>
/// Box2D Body Component
/// </summary>
class BodyComponent : public Component {
public:
	// Public Functions
	BodyComponent(float x, float y, float w, float h, b2World & world, float worldScale, std::string name, bool ignoreGravity);
	BodyComponent(float x, float y, float rad, b2World & world, float worldScale, std::string name, bool ignoreGravity);
	~BodyComponent();
	b2Body * getBody();
	bool isCircle();
	VectorAPI getDimensions();
	bool isOnGround();
	bool isLeftContact();
	bool isRightContact();
	bool isAiRightContact();
	void aiContactStart();
	void aiContactEnd();
	void groundContactStart();
	void groundContactEnd();
	void leftContactStart();
	void leftContactEnd();
	void rightContactStart();
	void rightContactEnd();
	int getBulletHitCount();
	void setBulletHitCount(int count);
	void setInitialPos(b2Vec2 pos);
	void setPosition(const b2Vec2 & pos);
	b2Vec2 getInitialPos();
	void resetPos();
	bool m_AiContact;
private:
	// Private Functions
	void init(float x, float y, float w, float h, bool ignoreGravity);

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
	CollisionData m_bodyData;
	b2Vec2 m_initialPosition;

	// Sensor Bodies

	// Ground
	b2PolygonShape * m_groundSensorShape;
	b2FixtureDef m_groundFixtureDef;
	bool m_onGround;
	CollisionData m_groundData;

	// Left
	b2PolygonShape * m_leftSensorShape;
	b2FixtureDef m_leftFixtureDef;
	bool m_leftContact;
	CollisionData m_leftData;

	// Right
	b2PolygonShape * m_rightSensorShape;
	b2FixtureDef m_rightFixtureDef;
	bool m_rightContact;
	CollisionData m_rightData;

	// Bullet
	int m_bulletHitCount;

	// AiRight
	b2PolygonShape * m_AiSensorShape;
	b2FixtureDef m_AiFixtureDef;
	
	CollisionData m_AiData;
};

#endif // !BODYCOMPONENT_H
