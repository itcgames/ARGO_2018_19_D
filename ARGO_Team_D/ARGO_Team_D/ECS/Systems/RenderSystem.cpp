#include "RenderSystem.h"

/// <summary>
/// Override the addEntity() method
/// </summary>
/// <param name="e">Entity to be added</param>
void RenderSystem::addEntity(Entity * e)
{	
	std::vector<std::string> allowedTypes{ "Position", "Sprite", "Animation"};
	auto comps = e->getComponentsOfType(allowedTypes);
	if (comps.size() >= allowedTypes.size() - 1)
	{
		RenderComponents c;
		c.position = dynamic_cast<PositionComponent*>(comps["Position"]);
		c.sprite = dynamic_cast<SpriteComponent*>(comps["Sprite"]);
		c.animation = dynamic_cast<AnimationComponent*>(comps["Animation"]);
		m_components.insert(std::make_pair(e->id, c));
		m_entityList.push_back(e);
	}
}

/// <summary>
/// draws each entity at their position.
/// </summary>
/// <param name="renderer"></param>
void RenderSystem::render(SDL_Renderer* renderer, Camera & camera)
{
	SDL_Rect bounds = camera.getBounds();
	for (auto & test : m_components) {
		auto rc = test.second;
		PositionComponent * p = rc.position;
		SpriteComponent * s = rc.sprite;
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

		AnimationComponent * a = rc.animation;
		if (s->getRender())
		{
			if (a) {
				SDL_RenderCopyEx(renderer, s->getTexture(), &a->getCurrentFrame(), &dest, s->m_angle, s->m_center, s->m_flip);
			}
			else {
				SDL_RenderCopyEx(renderer, s->getTexture(), NULL, &dest, s->m_angle, s->m_center, s->m_flip);
			}
		}
	}
	
}

void RenderSystem::removeEntity(const int id)
{
	auto comp = m_components.find(id);
	if (comp != m_components.end()) {
		m_components.erase(comp);
	}
	m_entityList.erase(std::remove_if(m_entityList.begin(), m_entityList.end(), [id](Entity* en) {
		return en->id == id; 
	}), m_entityList.end());
}
