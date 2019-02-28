#ifndef FACTORY_H
#define FACTORY_H

#include "..//ECS/Entities/Entity.h"
#include "..//Resource Manager/ResourceManager.h"
#include "..//ECS/Components/PositionComponent.h"
#include "..//ECS/Components/SpriteComponent.h"
#include "..//ECS/Components/BodyComponent.h"
#include "..//ECS/Components/AnimationComponent.h"
#include "..//ECS/Components/AiComponent.h"
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

/// <summary>
/// Base Factory class.
/// </summary>
class Factory {
public:
	Factory(ResourceManager * rm, b2World & world, const float SCALE, SDL_Renderer * rend);
	virtual Entity * create(std::string spriteId, VectorAPI dimensions, VectorAPI pos) = 0;
	virtual Entity * createOnlinePlayer(std::string spriteId, VectorAPI dimensions, VectorAPI pos) = 0;
	virtual Enemy * createGunEnemy() = 0;
	virtual Enemy * createFlyEnemy() = 0;
	virtual Enemy * createBigEnemy() = 0;
protected:
	// Private Members
	ResourceManager * m_resourceManager;
	b2World & m_refWorld;
	const float WORLD_SCALE;
	SDL_Renderer * m_renderer;
};

#endif
