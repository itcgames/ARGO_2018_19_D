#include "Bullet.h"

Bullet::Bullet(b2World & world, const float SCALE, ResourceManager * resourceManager, VectorAPI posIn, float speedIn, bool isPlayer)
	: m_refWorld(world),
	WORLD_SCALE(SCALE),
	m_resourceManager(resourceManager),
	m_isActive(true),
	m_speed(speedIn),
	m_ttl(3.f),
	m_dimensions(30, 10)
{
	// Box2D
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position = b2Vec2(posIn.x / WORLD_SCALE, posIn.y / WORLD_SCALE);
	m_body = m_refWorld.CreateBody(&m_bodyDef);
	b2PolygonShape * polygonShape = new b2PolygonShape();
	polygonShape->SetAsBox((m_dimensions.x / 2.f) / WORLD_SCALE, (m_dimensions.y / 2.f) / WORLD_SCALE);
	m_shape = polygonShape;
	m_fixtureDef.density = 1.f;
	m_fixtureDef.friction = 0.1f;
	m_fixtureDef.restitution = 0.0f;
	m_fixtureDef.shape = m_shape;
	m_fixtureDef.isSensor = true;
	m_body->CreateFixture(&m_fixtureDef);
	m_body->SetFixedRotation(true);

	// Texture
	m_texture = m_resourceManager->getImageResource("bullet");
}

Bullet::~Bullet()
{
	//m_refWorld.DestroyBody(m_body);
}

void Bullet::update(float dt)
{
	//m_ttl -= dt;
	if (m_ttl <= 0)
	{
		m_isActive = false;
	}
	else
	{
		auto bodyPos = m_body->GetPosition();
		m_body->SetLinearVelocity(b2Vec2(m_speed / WORLD_SCALE, 0));
		//m_body->SetTransform(b2Vec2(bodyPos.x + (m_speed / WORLD_SCALE) * dt, bodyPos.y), m_body->GetAngle());
	}
}

void Bullet::draw(SDL_Renderer * renderer, Camera & camera)
{
	if (m_isActive)
	{
		auto pos = m_body->GetPosition();
		m_dest.x = pos.x * WORLD_SCALE;
		m_dest.y = pos.y * WORLD_SCALE;
		m_dest.w = m_dimensions.x;
		m_dest.h = m_dimensions.y;
		SDL_RenderCopyEx(renderer, m_texture, NULL, &m_dest, 0, NULL, SDL_FLIP_NONE);
	}
}

void Bullet::collide()
{
	m_refWorld.DestroyBody(m_body);
	m_isActive = false;
}

bool Bullet::isActive()
{
	return m_isActive;
}
