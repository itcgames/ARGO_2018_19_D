#include "AiSystem.h"

AiSystem::AiSystem(BulletManager * bulletManager, BodyComponent * playerBody, const float SCALE, LevelData* levelData , Camera & camera)
	: m_bulletManager(bulletManager),
	m_playerBody(playerBody),
	WORLD_SCALE(SCALE),
	DISTANCE_THRESHOLD(7.f),
	GUN_ENEMY_ROF_MS(600.f),
	BIG_ENEMY_ROF_MS(800.f),
	GUN_ENEMY_SPEED(10.f),
	FLY_ENEMY_SPEED(12.f),
	BIG_ENEMY_SPEED(5.f),
	m_levelData(levelData)
{
	m_cam = &camera;
	m_allowedTypes = { "Body", "Animation", "Ai", "Sprite", "Particle" };

	groan = Mix_LoadWAV("ASSETS/SOUNDS/grunt.wav");
	Mix_VolumeChunk(groan, 128/4);

	shoot = Mix_LoadWAV("ASSETS/SOUNDS/pistol.wav");
	Mix_VolumeChunk(shoot, 128/4);
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

void AiSystem::update(float dt)
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

			if (Mix_PlayChannel(-1, groan, 0) == -1)
			{
				//return 1;
			}

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
					handleGroundEnemy(ac, dt);
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

void AiSystem::handleGroundEnemy(AiComponents & ac, float dt)
{
	// Get Variables
	auto body = ac.body->getBody();
	auto bodyPos = body->GetPosition();
	auto bodyVel = body->GetLinearVelocity();
	int minX = ac.ai->getMinX();
	int maxX = ac.ai->getMaxX();
	int direction = ac.ai->getDirection();
	float speed = ac.ai->getType() == EnemyGun ? GUN_ENEMY_SPEED : BIG_ENEMY_SPEED;
	float shotRof = ac.ai->getType() == EnemyGun ? GUN_ENEMY_ROF_MS : BIG_ENEMY_ROF_MS;

	// Process
	b2Vec2 dist = m_playerBody->getBody()->GetPosition() - bodyPos;
	if (DISTANCE_THRESHOLD > dist.Length())
	{
		ac.ai->setShotTimer(ac.ai->getShotTimer() + dt);
		std::cout << dt << std::endl;
		if(ac.ai->getShotTimer() > shotRof)
		{
			if (Mix_PlayChannel(-1, shoot, 0) == -1)
			{
				//return 1;
			}
			ac.ai->setShotTimer(0.f);
			m_bulletManager->createBullet(VectorAPI(bodyPos.x * WORLD_SCALE, bodyPos.y * WORLD_SCALE + ac.body->getDimensions().y / 4.f), direction * 50.f, false);
		}
		body->SetLinearVelocity(b2Vec2(0, 0));
		ac.animation->handleInput("Idle");
		direction = dist.x < 0 ? 1 : -1;
		ac.ai->setDirection(-direction);
		ac.sprite->m_flip = direction < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	}
	else
	{
		ac.ai->setShotTimer(0.f);
		if (direction < 0)
		{
			if ((bodyPos.x) > minX / WORLD_SCALE)
			{
				body->SetLinearVelocity(b2Vec2(-speed, bodyVel.y));
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
				body->SetLinearVelocity(b2Vec2(speed, bodyVel.y));
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

		dist.Normalize();
		dist *= FLY_ENEMY_SPEED;
		body->SetLinearVelocity(dist);
		ac.animation->handleInput("Walking");
		direction = dist.x < 0 ? 1 : -1;
		ac.ai->setDirection(-direction);
		ac.sprite->m_flip = direction < 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
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
				newVelocity *= FLY_ENEMY_SPEED;
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
				newVelocity *= FLY_ENEMY_SPEED;
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

