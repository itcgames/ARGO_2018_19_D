#include "Factory.h"

Factory::Factory(ResourceManager * rm, b2World & world, const float SCALE, SDL_Renderer * rend) :
	m_resourceManager(rm), 
	m_refWorld(world), 
	WORLD_SCALE(SCALE),
	m_renderer(rend)
{
}
