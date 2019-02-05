#include "RenderSystem.h"
#include <iostream>
#include "../Components/Components.h"
#include "../Components/SpriteComponent.h"

/// <summary>
/// draws each entity at their position.
/// </summary>
/// <param name="renderer"></param>
void RenderSystem::render(SDL_Renderer* renderer)
{
	std::vector<std::string> allowedTypes{ "Position", "Sprite" };
	for (Entity* i : m_entityList) {
		auto comps = i->getComponentsOfType(allowedTypes);
		if (comps.size() == allowedTypes.size()) {
			PositionComponent * p = dynamic_cast<PositionComponent*>(comps["Position"]);
			std::cout << "Pos: " << p->getPosition().x << ", " << p->getPosition().y << std::endl;

			SpriteComponent * s = dynamic_cast<SpriteComponent*>(comps["Sprite"]);
		}
	}
}