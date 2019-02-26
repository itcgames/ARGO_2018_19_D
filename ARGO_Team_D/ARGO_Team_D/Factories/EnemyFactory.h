#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "..//ECS/Entities/Entity.h"
#include "..//Resource Manager/ResourceManager.h"
#include "..//ECS/Components/PositionComponent.h"
#include "..//ECS/Components/SpriteComponent.h"
#include "..//ECS/Components/BodyComponent.h"
#include "..//ECS/Components/AnimationComponent.h"
#include "..//ECS/Components/AiComponent.h"
#include "..//Client/Client.h"
#include "../ECS/Components/ParticleEffectsComponent.h"

struct Enemy
{
	Entity * entity = nullptr;
	PositionComponent * position = nullptr;
	BodyComponent * body = nullptr;
	SpriteComponent * sprite = nullptr;
	AnimationComponent * animation = nullptr;
	AiComponent * ai = nullptr;
	ParticleEffectsComponent * part = nullptr;
};

class EnemyFactory
{
public:
	// Public Functions
	EnemyFactory(ResourceManager * rm, b2World & world, const float SCALE, SDL_Renderer * rend);
	~EnemyFactory();
	Enemy * createGunEnemy();
	Enemy * createFlyEnemy();
	Enemy * createBigEnemy();

private:
	// Private Functions
	Enemy * createEnemy(string spriteId, int idleFrames, int walkingFrames, int width, int height, bool flying);

	// Private Members
	ResourceManager * m_resourceManager;
	b2World & m_refWorld;
	const float WORLD_SCALE;
	SDL_Renderer * m_renderer;
};

#endif // !ENEMYFACTORY_H