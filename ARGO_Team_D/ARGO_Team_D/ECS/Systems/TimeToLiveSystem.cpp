#include "TimeToLiveSystem.h"

TimeToLiveSystem::TimeToLiveSystem()
{
	m_allowedTypes.push_back("TimeToLive");
	m_allowedTypes.push_back("Sprite");
}

void TimeToLiveSystem::update()
{
	for (Entity* i : m_entityList) 
	{
		auto comps = i->getComponentsOfType(m_allowedTypes);
		TimeToLiveComponent * t = dynamic_cast<TimeToLiveComponent*>(comps["TimeToLive"]);
		SpriteComponent * a = dynamic_cast<SpriteComponent*>(comps["Sprite"]);
		if (t->isActive())
		{
			if (!a->getRender())
			{
				a->setRender(true);
			}
			
			float time = (SDL_GetTicks() - t->getStart()) / 1000;
			if (t->getTTL() <= time)
			{
				t->setActive(false);

				if (a != nullptr)
				{
					a->setRender(false);
				}
			}
		}
		
	}
	
}
