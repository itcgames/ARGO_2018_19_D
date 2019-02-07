#include "CharacterFactory.h"

Entity * CharacterFactory::CreateEntityPlayer(std::string imageId, int entityId, VectorAPI pos, int width, int height)
{
	Entity* m_entity = new Entity(entityId);
	m_entity->addComponent(new PositionComponent(pos));
	m_entity->addComponent(new SpriteComponent(imageId, *m_resourceManager, width, height));

	return m_entity;
}
