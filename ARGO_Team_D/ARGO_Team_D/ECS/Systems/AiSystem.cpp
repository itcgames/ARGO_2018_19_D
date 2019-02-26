#include "AiSystem.h"

AiSystem::AiSystem(BulletManager * bulletManager, BodyComponent * playerBody, const float SCALE, LevelData* levelData , Camera & camera)
	: m_bulletManager(bulletManager),
	m_playerBody(playerBody),
	WORLD_SCALE(SCALE),
	DISTANCE_THRESHOLD(7.f),
	m_levelData(levelData)
{
	m_cam = &camera;
	m_allowedTypes = { "Body", "Animation", "Ai", "Sprite", "Particle" };
}

AiSystem::~AiSystem()
{
}

void AiSystem::addEntity(Entity * e)
{
	auto comps = e->getComponentsOfType(m_allowedTypes);
	if (comps.size() >= m_allowedTypes.size() - 1)
	{
		AiComponents aiComp;
		aiComp.body = dynamic_cast<BodyComponent*>(comps["Body"]);
		aiComp.animation = dynamic_cast<AnimationComponent*>(comps["Animation"]);
		aiComp.ai = dynamic_cast<AiComponent*>(comps["Ai"]);
		aiComp.sprite = dynamic_cast<SpriteComponent*>(comps["Sprite"]);
		aiComp.part = dynamic_cast<ParticleEffectsComponent*>(comps["Particle"]);
		m_components.insert(std::make_pair(e->id, aiComp));
		m_entityList.push_back(e);
	}
}

void AiSystem::update()
{
	for (auto & comp : m_components)
	{
		auto & ac = comp.second;
		auto body = ac.body->getBody();
		if (ac.body->getBulletHitCount() >= ac.ai->getMaxHits())
		{
			ac.part->m_emitterExplos.activate(true, (ac.body->getBody()->GetPosition().x * WORLD_SCALE),
				(ac.body->getBody()->GetPosition().y * WORLD_SCALE));
			m_levelData->enemyKilled();
			ac.ai->setActivationState(false);
			ac.body->setBulletHitCount(0); // Reset bullet hit count
			body->SetTransform(b2Vec2(-1000, 0), body->GetAngle());
		}
		else
		{
			bool active = ac.ai->getActivationState();
			ac.sprite->setRender(active);
			
			if (active)
			{
				if (AiType::EnemyFly == ac.ai->getType())
				{
					handleFlyEnemy(ac);
				}
				else
				{
					handleGroundEnemy(ac);
				}
			}
			else
			{
				body->SetLinearVelocity(b2Vec2(0, 0));
			}
		}	

		ac.part->m_emitter.setDirection(ac.ai->getDirection());
	}
}

void AiSystem::removeEntity(const int id)
{
	auto comp = m_components.find(id);
	if (comp != m_components.end()) {
		m_components.erase(comp);
	}
	m_entityList.erase(std::remove_if(m_entityList.begin(), m_entityList.end(), [id](Entity* en) {
		return en->id == id;
	}), m_entityList.end());
}

void AiSystem::handleGroundEnemy(AiComponents & ac)
{
	// Get Variables
	auto body = ac.body->getBody();
	auto bodyPos = body->GetPosition();
	auto bodyVel = body->GetLinearVelocity();
	int minX = ac.ai->getMinX();
	int maxX = ac.ai->getMaxX();
	int direction = ac.ai->getDirection();

	// Process
	b2Vec2 dist = m_playerBody->getBody()->GetPosition() - bodyPos;
	if (DISTANCE_THRESHOLD > dist.Length())
	{
		body->SetLinearVelocity(b2Vec2(0, 0));
		ac.animation->handleInput("Idle");
	}
	else
	{
		if (direction < 0)
		{
			if ((bodyPos.x) > minX / WORLD_SCALE)
			{
				body->SetLinearVelocity(b2Vec2(-10, bodyVel.y));
				ac.animation->handleInput("Walking");
			}
			else
			{
				ac.ai->setDirection(-direction);
				ac.sprite->m_flip = direction < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
			}
		}
		else if (direction > 0)
		{
			if ((bodyPos.x) < maxX / WORLD_SCALE)
			{
				body->SetLinearVelocity(b2Vec2(10, bodyVel.y));
				ac.animation->handleInput("Walking");
			}
			else
			{
				ac.ai->setDirection(-direction);
				ac.sprite->m_flip = direction < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
			}
		}
	}
}

void AiSystem::handleFlyEnemy(AiComponents & ac)
{
	// Get Variables
	auto body = ac.body->getBody();
	auto bodyPos = body->GetPosition();
	auto bodyVel = body->GetLinearVelocity();
	int minX = ac.ai->getMinX();
	int maxX = ac.ai->getMaxX();
	int direction = ac.ai->getDirection();

	// Process
	b2Vec2 dist = m_playerBody->getBody()->GetPosition() - bodyPos;
	if (DISTANCE_THRESHOLD > dist.Length())
	{
		body->SetLinearVelocity(b2Vec2(0, 0));
		ac.animation->handleInput("Idle");
	}
	else
	{
		b2Vec2 newVelocity = b2Vec2(0, ac.body->getInitialPos().y - bodyPos.y);
		if (direction < 0)
		{
			if ((bodyPos.x) > minX / WORLD_SCALE)
			{
				newVelocity.x = (minX / WORLD_SCALE) - bodyPos.x;
				newVelocity.Normalize();
				newVelocity *= 10.f;
				body->SetLinearVelocity(newVelocity);
				ac.animation->handleInput("Walking");
			}
			else
			{
				ac.ai->setDirection(-direction);
				ac.sprite->m_flip = direction < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
			}
		}
		else if (direction > 0)
		{
			if ((bodyPos.x) < maxX / WORLD_SCALE)
			{
				newVelocity.x = (maxX / WORLD_SCALE) - bodyPos.x;
				newVelocity.Normalize();
				newVelocity *= 10.f;
				body->SetLinearVelocity(newVelocity);
				ac.animation->handleInput("Walking");
			}
			else
			{
				ac.ai->setDirection(-direction);
				ac.sprite->m_flip = direction < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
			}
		}
	}
}

