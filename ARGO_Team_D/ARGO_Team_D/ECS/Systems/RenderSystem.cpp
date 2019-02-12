#include "RenderSystem.h"
#include <iostream>
#include "../Components/Components.h"
#include "../Components/PositionComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Utils/VectorAPI.h"

/// <summary>
/// draws each entity at their position.
/// </summary>
/// <param name="renderer"></param>
void RenderSystem::render(SDL_Renderer* renderer, Camera & camera)
{
	std::vector<std::string> allowedTypes{ "Position", "Sprite"};
	for (Entity* i : m_entityList) {
		auto comps = i->getComponentsOfType(allowedTypes);
		if (comps.size() == allowedTypes.size()) {
			PositionComponent * p = dynamic_cast<PositionComponent*>(comps["Position"]);
			SpriteComponent * s = dynamic_cast<SpriteComponent*>(comps["Sprite"]);

			SDL_Rect bounds = camera.getBounds();
			VectorAPI pos = p->getPosition();
			VectorAPI size(s->m_width, s->m_height);

			if (pos.x + size.x < bounds.x || pos.x > bounds.x + bounds.w
				|| pos.y + size.y < bounds.y || pos.y > bounds.y + bounds.h) {
				continue;
			}
			dest.x = pos.x - bounds.x;
			dest.y = pos.y - bounds.y;
			dest.w = s->m_width;
			dest.h = s->m_height;

			std::vector<std::string> type = { "Animation" };
			auto animationComps = i->getComponentsOfType(type);
			if (!animationComps.empty()) {
				AnimationComponent * a = dynamic_cast<AnimationComponent*>(animationComps["Animation"]);
				SDL_RenderCopyEx(renderer, s->getTexture(), &a->getCurrentFrame(), &dest, s->m_angle, s->m_center, s->m_flip);
			}
			else {
				SDL_RenderCopyEx(renderer, s->getTexture(), NULL, &dest, s->m_angle, s->m_center, s->m_flip);
			}
		}
	}
}