#include "EnemyFactory.h"

EnemyFactory::EnemyFactory(ResourceManager * rm, b2World & world, const float SCALE, SDL_Renderer * rend) :
	Factory(rm, world, SCALE, rend)
{
}

EnemyFactory::~EnemyFactory()
{
}

Enemy * EnemyFactory::createGunEnemy()
{
	Enemy * enemy = createEnemy("GunEnemy", 8, 8, 64, 64, false);
	enemy->ai = new AiComponent(EnemyGun, 0, 0, 5);
	auto p = new ParticleEffectsComponent(enemy->body->getBody()->GetPosition().x * WORLD_SCALE,
		enemy->body->getBody()->GetPosition().y * WORLD_SCALE,
		5, 5, SDL_Color{ 181, 101, 29 }, SDL_Color{ 255, 0, 0 },
		m_renderer, false, 45);
	p->m_emitter.setEmitting(false);
	enemy->part = p;


	enemy->entity->addComponent(enemy->ai);
	enemy->entity->addComponent(enemy->part);
	return enemy;
}

Enemy * EnemyFactory::createFlyEnemy()
{
	Enemy * enemy = createEnemy("FlyEnemy", 8, 8, 64, 64, true);
	enemy->ai = new AiComponent(EnemyFly, 0, 0, 1);
	auto p = new ParticleEffectsComponent(enemy->body->getBody()->GetPosition().x * WORLD_SCALE,
		enemy->body->getBody()->GetPosition().y * WORLD_SCALE,
		5, 5, SDL_Color{ 168, 120, 250 }, SDL_Color{ 235, 115, 0 },
		m_renderer, false, 45);
	p->emit = false;
	enemy->part = p;

	enemy->entity->addComponent(enemy->ai);
	enemy->entity->addComponent(enemy->part);
	return enemy;
}

Enemy * EnemyFactory::createBigEnemy()
{
	Enemy * enemy = createEnemy("BigEnemy", 8, 8, 128, 128, false);
	enemy->ai = new AiComponent(EnemyBig, 0, 0, 15);
	auto p = new ParticleEffectsComponent(enemy->body->getBody()->GetPosition().x * WORLD_SCALE,
		enemy->body->getBody()->GetPosition().y * WORLD_SCALE,
		5, 5, SDL_Color{ 181, 101, 29 }, SDL_Color{ 255, 0, 0 },
		m_renderer, false, 45);
	p->m_emitter.setEmitting(false);
	enemy->part = p;

	enemy->entity->addComponent(enemy->ai);
	enemy->entity->addComponent(enemy->part);
	return enemy;
}

Enemy * EnemyFactory::createEnemy(string spriteId, int idleFrameCount, int walkingFrameCount, int width, int height, bool flying)
{
	// Create Enemy
	Enemy * enemy = new Enemy();
	enemy->entity = new Entity();

	// Create Components
	enemy->position = new PositionComponent(-1000, -1000);
	enemy->sprite = new SpriteComponent(spriteId, *m_resourceManager, width, height);
	enemy->body = new BodyComponent(-1000, -1000, width, m_refWorld, WORLD_SCALE, flying ? "FlyEnemyBody" : "EnemyBody", flying);
	AnimationComponent * a = new AnimationComponent();

	// Setup Animation
	std::vector<SDL_Rect> idleFrames;
	for (int i = 0; i < idleFrameCount; ++i)
	{
		SDL_Rect frame = { i * width, 0, width, height };
		idleFrames.push_back(frame);
	}
	a->addAnimation("Idle", idleFrames, 1, 1, true);
	std::vector<SDL_Rect> walkingFrames;
	for (int i = 0; i < walkingFrameCount; ++i)
	{
		SDL_Rect frame = { i * width, height, width, height };
		walkingFrames.push_back(frame);
	}
	a->addAnimation("Walking", walkingFrames, 1, 2, true);

	enemy->animation = a;

	// Add Components
	enemy->entity->addComponent(enemy->position);
	enemy->entity->addComponent(enemy->sprite);
	enemy->entity->addComponent(enemy->body);
	enemy->entity->addComponent(enemy->animation);
	
	return enemy;
}