#include "TimeToLiveSystem.h"

TimeToLiveSystem::TimeToLiveSystem()
{
	m_allowedTypes.push_back("TimeToLive");
}

void TimeToLiveSystem::update()
{
	for (Entity* i : m_entityList) 
	{
		auto comps = i->getComponentsOfType(m_allowedTypes);
		TimeToLiveComponent * t = dynamic_cast<TimeToLiveComponent*>(comps["TimeToLive"]);
		
		if (t->isActive())
		{
			float time = (SDL_GetTicks() - t->getStart()) / 1000;
			if (t->getTTL() <= time)
			{
				t->setActive(false);
			}
		}
		
	}
	
}
