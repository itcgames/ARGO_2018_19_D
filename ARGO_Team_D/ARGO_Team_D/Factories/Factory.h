#ifndef FACTORY_H
#define FACTORY_H

#include "..//ECS/Entities/Entity.h"
#include "..//Resource Manager/ResourceManager.h"
#include "..//ECS/Components/PositionComponent.h"
#include "..//ECS/Components/SpriteComponent.h"

/// <summary>
/// Base Factory class.
/// </summary>
class Factory {
public:

	virtual Entity* CreateEntityPlayer(std::string imageId, int entityId, VectorAPI pos, int width, int height) = 0;
};

#endif
