#include "ControlSystem.h"

ControlSystem::ControlSystem()
{
	allowedTypes = { "Body", "Position", "Gun", "Sprite" };
	direction = 1;
}

ControlSystem::~ControlSystem()
{
}

void ControlSystem::addEntity(Entity * e)
{
	std::vector<std::string> allowedTypes{ "Body" , "Animation", "Particle", "Sprite" };
	auto comps = e->getComponentsOfType(allowedTypes);
	if (comps.size() >= allowedTypes.size() - 1)
	{
		ControlComponents c;
		c.body = dynamic_cast<BodyComponent*>(comps["Body"]); 
		c.animation = dynamic_cast<AnimationComponent*>(comps["Animation"]);
		c.sprite = dynamic_cast<SpriteComponent*>(comps["Sprite"]);
		c.part = dynamic_cast<ParticleEffectsComponent*>(comps["Particle"]);
		m_components.insert(std::make_pair(e->id, c));
		m_entityList.push_back(e);
	}
}

void ControlSystem::update()
{
	for (auto & comp : m_components)
	{
		auto & cc = comp.second;
		BodyComponent * body = cc.body;

		if (cc.part != nullptr)
		{
			cc.part->m_emitter.setDirection(direction);
		}

		if (body != nullptr)
		{
			b2Body * b2Body = body->getBody();
			b2Vec2 currentVelocity = b2Body->GetLinearVelocity();
			if (m_jump && body->isOnGround())
			{
				b2Body->SetLinearVelocity(b2Vec2(currentVelocity.x, -35));
				currentVelocity.y = -35;
			}
			if (m_moveRight)
			{
				b2Body->SetLinearVelocity(b2Vec2(15, currentVelocity.y));
				currentVelocity.x = 15;
				cc.sprite->m_flip = SDL_FLIP_NONE;
				cc.animation->handleInput("Walking");
			}
			else if (m_moveLeft)
			{
				b2Body->SetLinearVelocity(b2Vec2(-15, currentVelocity.y));
				currentVelocity.x = -15;
				cc.sprite->m_flip = SDL_FLIP_HORIZONTAL;
				cc.animation->handleInput("Walking");
			}
			else
			{
				b2Body->SetLinearVelocity(b2Vec2(0, currentVelocity.y));
				currentVelocity.x = 0;
				cc.animation->handleInput("Idle");
			}

			if (m_fire)
			{
				spawnProjectile(b2Body->GetPosition().x * 30.0f, b2Body->GetPosition().y * 30.0f);
			}
			m_moveRight = false, m_moveLeft = false, m_jump = false, m_fire = false;
		}
	}
}

void ControlSystem::moveRight()
{
	m_moveRight = true;
	direction = 1;
}

void ControlSystem::moveLeft()
{
	m_moveLeft = true;
	direction = -1;
}

void ControlSystem::jump()
{
	m_jump = true;
}

void ControlSystem::fire()
{
	m_fire = true;	
}

void ControlSystem::bindBullets(BulletManager * bulletManager)
{
	m_bulletManager = bulletManager;
}

void ControlSystem::spawnProjectile(float x, float y)
{
	// Add fire rate
	m_bulletManager->createBullet(VectorAPI(x + 50 * direction, y), 50 * direction, true);
}

void ControlSystem::removeEntity(const int id)
{
	auto comp = m_components.find(id);
	if (comp != m_components.end()) {
		m_components.erase(comp);
	}
	m_entityList.erase(std::remove_if(m_entityList.begin(), m_entityList.end(), [id](Entity* en) {
		return en->id == id;
	}), m_entityList.end());
}
