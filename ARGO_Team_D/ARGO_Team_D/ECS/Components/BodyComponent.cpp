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
BodyComponent::BodyComponent(float x, float y, float w, float h, b2World & world, float worldScale, std::string name, bool ignoreGravity)
	: m_refWorld(world),
	m_worldScale(worldScale),
	m_isCircle(false),
	m_dimensions(w, h),
	m_bodyData(name, this),
	m_onGround(false),
	m_groundData("BodyGround", this),
	m_leftContact(false),
	m_leftData("BodyLeft", this),
	m_rightContact(false),
	m_rightData("BodyRight", this),
	m_bulletHitCount(0),
	m_AiContact(false),
	m_AiData("BodyAiRight", this)
{
	float halfWidth = w / 2.f;
	float halfHeight = h / 2.f;
	b2PolygonShape * polygonShape = new b2PolygonShape();
	polygonShape->SetAsBox(halfWidth / m_worldScale, halfHeight / m_worldScale);
	m_shape = polygonShape;
	init(x, y, w, h, ignoreGravity);
}

/// <summary>
/// Body component constructor used to create a circle Box2D for an entity
/// </summary>
/// <param name="x">X position of the entity</param>
/// <param name="y">Y position of the entity</param>
/// <param name="rad">Radius of the entity</param>
/// <param name="world">Reference to the Box2D world</param>
/// <param name="worldScale">The scale used for Box2D</param>
BodyComponent::BodyComponent(float x, float y, float rad, b2World & world, float worldScale, std::string name, bool ignoreGravity)
	: m_refWorld(world),
	m_worldScale(worldScale),
	m_isCircle(true),
	m_dimensions(rad, rad),
	m_bodyData(name, this),
	m_onGround(false),
	m_groundData("BodyGround", this),
	m_leftContact(false),
	m_leftData("BodyLeft", this),
	m_rightContact(false),
	m_rightData("BodyRight", this),
	m_bulletHitCount(0),
	m_AiContact(false),
	m_AiData("BodyAiRight", this)
{
	float halfRad = rad / 2.f;
	b2CircleShape * circleShape = new b2CircleShape();
	circleShape->m_radius = halfRad / m_worldScale;
	m_shape = circleShape;
	init(x, y, rad, rad, ignoreGravity);
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
/// Function used to check whether the Box2D body is currently toucing something on the left
/// </summary>
/// <returns>Bool representing whether the body is contacting the left</returns>
bool BodyComponent::isLeftContact()
{
	return m_leftContact;
}

/// <summary>
/// Function used to check whether the Box2D body is currently toucing something on the left
/// </summary>
/// <returns>Bool representing whether the body is contacting the right</returns>
bool BodyComponent::isRightContact()
{
	return m_rightContact;
}

bool BodyComponent::isAiRightContact()
{
	return m_AiContact;
}

void BodyComponent::aiContactStart()
{
	m_AiContact = true;
}

void BodyComponent::aiContactEnd()
{
	m_AiContact = false;

}

/// <summary>
/// Init is used to reduce code repetition in the constructor functions
/// common code is here
/// </summary>
/// <param name="x">X position passed in constrcutor</param>
/// <param name="y">Y position passed in </param>
/// <param name="w">Width of Box2D rect (or radius of circle)</param>
/// <param name="h">Height of Box2D rect (or radius of circle)</param>
void BodyComponent::init(float x, float y, float w, float h, bool ignoreGravity)
{
	id = "Body";
	float halfWidth = w / 2.f;
	float halfHeight = h / 2.f;
	m_initialPosition = b2Vec2((x + halfWidth) / m_worldScale, (y + halfHeight) / m_worldScale);
	m_bodyDef.position = m_initialPosition;
	m_bodyDef.type = b2_dynamicBody;
	m_body = m_refWorld.CreateBody(&m_bodyDef);
	m_body->SetGravityScale(ignoreGravity ? 0.0f : 1.0f);
	m_fixtureDef.density = 1.f;
	m_fixtureDef.friction = 0.1f;
	m_fixtureDef.restitution = 0.0f;
	m_fixtureDef.shape = m_shape;
	m_fixtureDef.userData = &m_bodyData;
	m_body->CreateFixture(&m_fixtureDef);
	m_body->SetFixedRotation(true);

	// Sensor checks if the body is on the ground
	m_groundSensorShape = new b2PolygonShape();
	m_groundSensorShape->SetAsBox((halfWidth / m_worldScale) / 2.f, (halfHeight / m_worldScale) / 10.f, b2Vec2(0, halfHeight / m_worldScale), 0);
	m_groundFixtureDef.shape = m_groundSensorShape;
	m_groundFixtureDef.isSensor = true;
	m_groundFixtureDef.userData = &m_groundData;
	m_groundFixtureDef.filter.categoryBits = 0x0004;
	m_groundFixtureDef.filter.maskBits = 0x0008;
	b2Fixture * footSensorFixture = m_body->CreateFixture(&m_groundFixtureDef);
	footSensorFixture->SetUserData(&m_groundData);

	// Sensor checks if the body has contact to the left
	m_leftSensorShape = new b2PolygonShape();
	m_leftSensorShape->SetAsBox((halfWidth / m_worldScale) / 10.f, (halfHeight / m_worldScale) / 2.f, b2Vec2(-halfWidth / m_worldScale, 0), 0);
	m_leftFixtureDef.shape = m_leftSensorShape;
	m_leftFixtureDef.isSensor = true;
	m_leftFixtureDef.userData = &m_leftData;
	m_leftFixtureDef.filter.categoryBits = 0x0004;
	m_leftFixtureDef.filter.maskBits = 0x0008;
	b2Fixture * leftSensorFixture = m_body->CreateFixture(&m_leftFixtureDef);
	leftSensorFixture->SetUserData(&m_leftData);

	// Sensor checks if the body has contact to the right
	m_rightSensorShape = new b2PolygonShape();
	m_rightSensorShape->SetAsBox((halfWidth / m_worldScale) / 2.f, (halfHeight / m_worldScale) / 10.f, b2Vec2(halfWidth / m_worldScale, 0), 0);
	m_rightFixtureDef.shape = m_rightSensorShape;
	m_rightFixtureDef.isSensor = true;
	m_rightFixtureDef.userData = &m_rightData;
	m_rightFixtureDef.filter.categoryBits = 0x0004;
	m_rightFixtureDef.filter.maskBits = 0x0008;
	b2Fixture * rightSensorFixture = m_body->CreateFixture(&m_rightFixtureDef);
	rightSensorFixture->SetUserData(&m_rightData);

	// Sensor checks if the body has contact to the bottom right
	m_AiSensorShape = new b2PolygonShape();
	m_AiSensorShape->SetAsBox((halfWidth / m_worldScale), (halfHeight / m_worldScale), b2Vec2((halfWidth * 2) / m_worldScale, halfHeight / m_worldScale), 0);
	m_AiFixtureDef.shape = m_AiSensorShape;
	m_AiFixtureDef.isSensor = true;
	m_AiFixtureDef.userData = &m_AiData;
	m_AiFixtureDef.filter.categoryBits = 0x0004;
	m_AiFixtureDef.filter.maskBits = 0x0008;
	b2Fixture * aiSensorFixture = m_body->CreateFixture(&m_AiFixtureDef);
	aiSensorFixture->SetUserData(&m_AiData);
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

/// <summary>
/// Function used by Box2D to inform Body Component that it's touching on its' left
/// </summary>
void BodyComponent::leftContactStart()
{
	m_leftContact = true;
}

/// <summary>
/// Function used by Box2D to inform Body Component that it's not touching on its' left
/// </summary>
void BodyComponent::leftContactEnd()
{
	m_leftContact = false;
}

/// <summary>
/// Function used by Box2D to inform Body Component that it's touching on its' right
/// </summary>
void BodyComponent::rightContactStart()
{
	m_rightContact = true;
}

/// <summary>
/// Function used by Box2D to inform Body Component that it's not touching on its' right
/// </summary>
void BodyComponent::rightContactEnd()
{
	m_rightContact = false;
}

/// <summary>
/// Function used to check how many times a body has been hit by a bullet
/// </summary>
/// <returns>int bullet hit count</returns>
int BodyComponent::getBulletHitCount()
{
	return m_bulletHitCount;
}

/// <summary>
/// Function allows bullet hit count to be set or reset
/// </summary>
/// <param name="count">Desired bullet hit count (generally used as a bullet count reset so 0)</param>
void BodyComponent::setBulletHitCount(int count)
{
	m_bulletHitCount = count;
}

void BodyComponent::setInitialPos(b2Vec2 pos)
{
	m_initialPosition = pos;
}

void BodyComponent::setPosition(const b2Vec2 & pos)
{
	m_body->SetTransform(pos, m_body->GetAngle());
}

b2Vec2 BodyComponent::getInitialPos()
{
	return m_initialPosition;
}

void BodyComponent::resetPos()
{
	m_body->SetTransform(m_initialPosition, m_body->GetAngle());
}
