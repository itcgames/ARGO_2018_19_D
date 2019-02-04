#include "RenderSystem.h"
#include <iostream>

/// <summary>
/// adds entity to list.
/// </summary>
/// <param name="en"></param>
void RenderSystem::addEntity(Entity * en)
{
	m_entityList.push_back(en);
}

/// <summary>
/// draws each entity at their position.
/// </summary>
/// <param name="renderer"></param>
void RenderSystem::render(SDL_Renderer* renderer)
{
	for (Entity* i : m_entityList) {

	}
}