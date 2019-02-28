#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H

#include "..//ECS/Entities/Entity.h"
#include "..//ECS/Components/AnimationComponent.h"
#include "..//ECS/Components/GunComponent.h"
#include "..//ECS/Components/ParticleEffectsComponent.h"
#include "../ECS/Components/NetworkComponent.h"
#include "..//Client/Client.h"
#include "..//ECS/Components/HealthComponent.h"
#include "Factory.h"


class PlayerFactory : public Factory
{
public:
	PlayerFactory(ResourceManager * rm, b2World & world, const float SCALE, SDL_Renderer * rend);
	Entity * create(std::string spriteId, VectorAPI dimensions, VectorAPI pos) override;
	Entity * createOnlinePlayer(std::string spriteId, VectorAPI dimensions, VectorAPI pos) override;
	Enemy * createGunEnemy() override { return nullptr; };
	Enemy * createFlyEnemy() override { return nullptr; };
	Enemy * createBigEnemy() override { return nullptr; };
};

#endif // !PLAYERFACTORY_H