#include "RenderSystem.h"
#include <iostream>
#include "../Components/Components.h"
#include "../Components/PositionComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Utils/VectorAPI.h"

/// <summary>
/// draws each entity at their position.
/// </summary>
/// <param name="renderer"></param>
void RenderSystem::render(SDL_Renderer* renderer, Camera & camera)
{
	std::vector<std::string> allowedTypes{ "Position", "Sprite" };
	for (Entity* i : m_entityList) {
		auto comps = i->getComponentsOfType(allowedTypes);
		if (comps.size() == allowedTypes.size()) {
			PositionComponent * p = dynamic_cast<PositionComponent*>(comps["Position"]);
			//std::cout << "Pos: " << p->getPosition().x << ", " << p->getPosition().y << std::endl;
			SpriteComponent * s = dynamic_cast<SpriteComponent*>(comps["Sprite"]);
			VectorAPI pos = p->getPosition();
			SDL_Rect bounds = camera.getBounds();
			dest.x = pos.x - bounds.x;
			dest.y = pos.y - bounds.y;
			dest.w = s->m_width;
			dest.h = s->m_height;
			SDL_RenderCopyEx(renderer, s->getTexture(), NULL, &dest, s->m_angle,s->m_center, s->m_flip);
		}
	}
}