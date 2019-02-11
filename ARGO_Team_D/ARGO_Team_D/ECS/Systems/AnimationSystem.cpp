#include "AnimationSystem.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"

AnimationSystem::AnimationSystem()
{
	m_allowedtypes = { "Sprite", "Animation" };
}

void AnimationSystem::update(const float & dt)
{
	for (auto e : m_entityList) {
		auto comps = e->getComponentsOfType(m_allowedtypes);
		if (comps.size() == m_allowedtypes.size()) {
			SpriteComponent * s = dynamic_cast<SpriteComponent*>(comps["Position"]);
			AnimationComponent * a = dynamic_cast<AnimationComponent*>(comps["Animation"]);

			a->update(dt);

		}
	}
}
