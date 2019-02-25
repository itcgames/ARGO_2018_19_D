#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H

#include "..//ECS/Entities/Entity.h"
#include "..//Resource Manager/ResourceManager.h"
#include "..//ECS/Components/PositionComponent.h"
#include "..//ECS/Components/SpriteComponent.h"
#include "..//ECS/Components/BodyComponent.h"
#include "..//ECS/Components/AnimationComponent.h"
#include "..//ECS/Components/GunComponent.h"
#include "..//ECS/Components/ParticleEffectsComponent.h"
#include "../ECS/Components/NetworkComponent.h"
#include "..//Client/Client.h"
#include "..//ECS/Components/HealthComponent.h"


class PlayerFactory
{
public:
	PlayerFactory(std::string spriteId, VectorAPI dimensions, ResourceManager * rm, b2World & world, const float SCALE, SDL_Renderer * rend);
	Entity * create(VectorAPI pos);
private:
	ResourceManager * m_resourceManager;
	b2World & m_refWorld;
	const float WORLD_SCALE;
	std::string m_spriteId;
	VectorAPI m_dimensions;
	SDL_Renderer * m_renderer;
};

#endif // !PLAYERFACTORY_H