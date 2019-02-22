#include "PlayerFactory.h"
#include <Box2D/Box2D.h>

PlayerFactory::PlayerFactory(std::string spriteId, VectorAPI dimensions, ResourceManager * rm, b2World & world, const float SCALE)
	: m_resourceManager(rm), 
	m_refWorld(world), 
	WORLD_SCALE(SCALE),
	m_spriteId(spriteId),
	m_dimensions(dimensions)
{
}

Entity * PlayerFactory::create(VectorAPI pos)
{
	Entity * e1 = new Entity();
	Entity * e2 = new Entity();
	Entity * e3 = new Entity();

	Entity * entity = new Entity();
	entity->addComponent(new PositionComponent(pos));
	entity->addComponent(new SpriteComponent(m_spriteId, *m_resourceManager, m_dimensions.x, m_dimensions.y));
	auto body = new BodyComponent(pos.x, pos.y, m_dimensions.x, m_refWorld, WORLD_SCALE);
	/*b2Filter test;
	test.categoryBits = 0x0001;
	body->getBody()->GetFixtureList()[0].SetFilterData(test);*/
	entity->addComponent(body);
	entity->addComponent(new GunComponent(0));
	entity->addComponent(new NetworkComponent(-1));
	return entity;
}

Entity * PlayerFactory::createOnlinePlayer(VectorAPI pos, int id)
{
	Entity * entity = new Entity();
	entity->addComponent(new PositionComponent(pos));
	entity->addComponent(new SpriteComponent(m_spriteId, *m_resourceManager, m_dimensions.x, m_dimensions.y));
	auto body = new BodyComponent(pos.x, pos.y, m_dimensions.x, m_refWorld, WORLD_SCALE);
	entity->addComponent(body);
	entity->addComponent(new GunComponent(0));
	entity->addComponent(new NetworkComponent(id));
	return entity;
}
