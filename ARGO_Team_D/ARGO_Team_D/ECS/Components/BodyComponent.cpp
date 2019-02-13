#include "BodyComponent.h"

/// <summary>
/// Body component constructor used to create a square Box2D for an entity
/// </summary>
/// <param name="x">X position of the entity</param>
/// <param name="y">Y position of the entity</param>
/// <param name="w">Width of the entity</param>
/// <param name="h">Height of th entity</param>
/// <param name="world">Reference to the Box2D world</param>
/// <param name="worldScale">The scale used for Box2D</param>
BodyComponent::BodyComponent(float x, float y, float w, float h, b2World & world, float worldScale)
	: m_refWorld(world),
	m_worldScale(worldScale),
	m_isCircle(false),
	m_dimensions(w, h),
	m_onGround(false)
{
	float halfWidth = w / 2.f;
	float halfHeight = h / 2.f;
	b2PolygonShape * polygonShape = new b2PolygonShape();
	polygonShape->SetAsBox(halfWidth / m_worldScale, halfHeight / m_worldScale);
	m_shape = polygonShape;
	init(x, y, w, h);
}

/// <summary>
/// Body component constructor used to create a circle Box2D for an entity
/// </summary>
/// <param name="x">X position of the entity</param>
/// <param name="y">Y position of the entity</param>
/// <param name="rad">Radius of the entity</param>
/// <param name="world">Reference to the Box2D world</param>
/// <param name="worldScale">The scale used for Box2D</param>
BodyComponent::BodyComponent(float x, float y, float rad, b2World & world, float worldScale)
	: m_refWorld(world),
	m_worldScale(worldScale),
	m_isCircle(true),
	m_dimensions(rad, rad),
	m_onGround(false)
{
	float halfRad = rad / 2.f;
	b2CircleShape * circleShape = new b2CircleShape();
	//circleShape->m_p.Set(halfRad, halfRad); // DEBUG
	circleShape->m_radius = halfRad / m_worldScale;
	m_shape = circleShape;
	init(x, y, rad, rad);
}

/// <summary>
/// Destructor function
/// </summary>
BodyComponent::~BodyComponent()
{
	m_refWorld.DestroyBody(m_body);
	delete m_shape;
}

/// <summary>
/// Function used to get a pointer to the Box2D body
/// </summary>
/// <returns>pointer to the Body</returns>
b2Body * BodyComponent::getBody()
{
	return m_body;
}

/// <summary>
/// Function used to return whether a body is a circle or not
/// </summary>
/// <returns>Bool representing whether a body is a circle</returns>
bool BodyComponent::isCircle()
{
	return m_isCircle;
}

/// <summary>
/// Function used to get the dimensions of a box2D body
/// </summary>
/// <returns>VectorAPI containing width and height of Box2D body</returns>
VectorAPI BodyComponent::getDimensions()
{
	return m_dimensions;
}

/// <summary>
/// Function used to check whether the Box2D body is currently on the ground
/// </summary>
/// <returns>Bool representing whether the body is on the ground</returns>
bool BodyComponent::isOnGround()
{
	return m_onGround;
}

/// <summary>
/// Init is used to reduce code repetition in the constructor functions
/// common code is here
/// </summary>
/// <param name="x">X position passed in constrcutor</param>
/// <param name="y">Y position passed in </param>
/// <param name="w">Width of Box2D rect (or radius of circle)</param>
/// <param name="h">Height of Box2D rect (or radius of circle)</param>
void BodyComponent::init(float x, float y, float w, float h)
{
	id = "Body";
	float halfWidth = w / 2.f;
	float halfHeight = h / 2.f;
	m_bodyDef.position = b2Vec2((x + halfWidth) / m_worldScale, (y + halfHeight) / m_worldScale);
	m_bodyDef.type = b2_dynamicBody;
	m_body = m_refWorld.CreateBody(&m_bodyDef);
	m_fixtureDef.density = 1.f;
	m_fixtureDef.friction = 0.1f;
	m_fixtureDef.restitution = 0.0f;
	m_fixtureDef.shape = m_shape;
	m_body->CreateFixture(&m_fixtureDef);
	m_body->SetFixedRotation(true);

	// Sensor checks if the body is on the ground
	m_groundSensorShape = new b2PolygonShape();
	m_groundSensorShape->SetAsBox((halfWidth / m_worldScale) / 2.f, (halfHeight / m_worldScale) / 2.f, b2Vec2(0, halfHeight / m_worldScale), 0);
	m_groundFixtureDef.shape = m_groundSensorShape;
	m_groundFixtureDef.isSensor = true;
	b2Fixture * footSensorFixture = m_body->CreateFixture(&m_groundFixtureDef);
	footSensorFixture->SetUserData(this);
}

/// <summary>
/// Function used by Box2D to inform Body Component that it's on the ground
/// </summary>
void BodyComponent::groundContactStart()
{
	m_onGround = true;
}

/// <summary>
/// Function used by Box2D to inform Body Component that it's not on the ground
/// </summary>
void BodyComponent::groundContactEnd()
{
	m_onGround = false;
}