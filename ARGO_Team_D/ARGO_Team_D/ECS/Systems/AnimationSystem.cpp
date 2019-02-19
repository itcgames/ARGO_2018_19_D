#include "AnimationSystem.h"

AnimationSystem::AnimationSystem()
{
	m_allowedtypes = { "Sprite", "Animation" };
}

void AnimationSystem::addEntity(Entity * e)
{
	auto comps = e->getComponentsOfType(m_allowedtypes);
	if (comps.size() >= m_allowedtypes.size() - 1)
	{
		AnimationComponents a;
		a.sprite = dynamic_cast<SpriteComponent*>(comps["Sprite"]);
		a.animation = dynamic_cast<AnimationComponent*>(comps["Animation"]);
		m_components.insert(std::make_pair(e->id, a));
		m_entityList.push_back(e);
	}
}

void AnimationSystem::update(const float & dt)
{
	for (auto & comp : m_components) {
		auto & ac = comp.second;
		ac.animation->update(dt);
		ac.sprite->m_srcRect = ac.animation->getCurrentFrame();
	}
}

void AnimationSystem::removeEntity(const int id)
{
	auto comp = m_components.find(id);
	if (comp != m_components.end()) {
		m_components.erase(comp);
	}
	m_entityList.erase(std::remove_if(m_entityList.begin(), m_entityList.end(), [id](Entity* en) {
		return en->id == id;
	}), m_entityList.end());
}
