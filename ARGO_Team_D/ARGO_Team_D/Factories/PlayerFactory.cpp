#include "PlayerFactory.h"
#include <Box2D/Box2D.h>

PlayerFactory::PlayerFactory(ResourceManager * rm, b2World & world, const float SCALE, SDL_Renderer * rend) :
	Factory(rm, world, SCALE, rend)
{
}

Entity * PlayerFactory::create(std::string spriteId, VectorAPI dimensions, VectorAPI pos)
{
	Entity * entity = new Entity();
	entity->addComponent(new PositionComponent(pos));
	entity->addComponent(new SpriteComponent(spriteId, *m_resourceManager, dimensions.x, dimensions.y));
	auto body = new BodyComponent(pos.x, pos.y, dimensions.x, m_refWorld, WORLD_SCALE, "PlayerBody", false);
	auto part = new ParticleEffectsComponent(body->getBody()->GetPosition().x * WORLD_SCALE,
		body->getBody()->GetPosition().y * WORLD_SCALE,
		5, 5, SDL_Color{ 181, 101, 29 }, SDL_Color{ 255, 0, 0 },
		m_renderer, false, 45);
	part->m_emitter.setEmitting(true);
	part->m_emitter.setFramesPerEmission(5);
	part->m_emitter.setLooping(true);

	entity->addComponent(part);
	entity->addComponent(body);
	entity->addComponent(new HealthComponent(100,3));

	AnimationComponent * a = new AnimationComponent();
	std::vector<SDL_Rect> idleFrames;
	for (int i = 0; i < 4; ++i)
	{
		SDL_Rect frame = { i * 64, 0, 64, 64 };
		idleFrames.push_back(frame);
	}
	a->addAnimation("Idle", idleFrames, 1, 2, true);
	std::vector<SDL_Rect> walkingFrames;
	for (int i = 0; i < 8; ++i)
	{
		SDL_Rect frame = { i * 64, 64, 64, 64 };
		walkingFrames.push_back(frame);
	}
	a->addAnimation("Walking", walkingFrames, 1, 2, true);
	entity->addComponent(a);
	entity->addComponent(new NetworkComponent(-1));
	return entity;
}

Entity * PlayerFactory::createOnlinePlayer(std::string spriteId, VectorAPI dimensions, VectorAPI pos)
{
	Entity * entity = new Entity();
	entity->addComponent(new PositionComponent(pos));
	entity->addComponent(new SpriteComponent(spriteId, *m_resourceManager, dimensions.x, dimensions.y));
	//auto body = new BodyComponent(pos.x, pos.y, m_dimensions.x, m_refWorld, WORLD_SCALE, "PlayerBody", false);
	auto part = new ParticleEffectsComponent(pos.x,
		pos.y,
		5, 5, SDL_Color{ 181, 101, 29 }, SDL_Color{ 255, 0, 0 },
		m_renderer, false, 45);
	part->m_emitter.setEmitting(true);
	part->m_emitter.setFramesPerEmission(5);
	part->m_emitter.setLooping(true);

	entity->addComponent(part);
	//entity->addComponent(body);
	entity->addComponent(new GunComponent(0));

	AnimationComponent * a = new AnimationComponent();
	std::vector<SDL_Rect> idleFrames;
	for (int i = 0; i < 4; ++i)
	{
		SDL_Rect frame = { i * 64, 0, 64, 64 };
		idleFrames.push_back(frame);
	}
	a->addAnimation("Idle", idleFrames, 1, 2, true);
	std::vector<SDL_Rect> walkingFrames;
	for (int i = 0; i < 8; ++i)
	{
		SDL_Rect frame = { i * 64, 64, 64, 64 };
		walkingFrames.push_back(frame);
	}
	a->addAnimation("Walking", walkingFrames, 1, 2, true);
	entity->addComponent(a);
	entity->addComponent(new NetworkComponent(-1));
	return entity;
}
