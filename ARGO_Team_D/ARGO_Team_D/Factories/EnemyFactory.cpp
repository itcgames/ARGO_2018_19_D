#include "EnemyFactory.h"

EnemyFactory::EnemyFactory(ResourceManager * rm, b2World & world, const float SCALE)
	: m_resourceManager(rm),
	m_refWorld(world),
	WORLD_SCALE(SCALE)
{
}

EnemyFactory::~EnemyFactory()
{
}

Enemy * EnemyFactory::createGunEnemy()
{
	Enemy * enemy = createEnemy("GunEnemy", 8, 8, 64, 64, false);
	enemy->ai = new AiComponent(EnemyGun, 0, 0, 3);
	enemy->entity->addComponent(enemy->ai);
	return enemy;
}

Enemy * EnemyFactory::createFlyEnemy()
{
	Enemy * enemy = createEnemy("FlyEnemy", 8, 8, 64, 64, true);
	enemy->ai = new AiComponent(EnemyFly, 0, 0, 1);
	enemy->entity->addComponent(enemy->ai);
	return enemy;
}

Enemy * EnemyFactory::createBigEnemy()
{
	Enemy * enemy = createEnemy("BigEnemy", 8, 8, 128, 128, false);
	enemy->ai = new AiComponent(EnemyBig, 0, 0, 10);
	enemy->entity->addComponent(enemy->ai);
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