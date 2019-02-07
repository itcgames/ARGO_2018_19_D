#include "ControlSystem.h"

ControlSystem::ControlSystem()
{

}

ControlSystem::~ControlSystem()
{
}

void ControlSystem::handleInput(SDL_Keycode key)
{
	/*for (int i = 0; i < m_entityList.size(); i++)
	{
		ControlComponent * contComp = dynamic_cast<ControlComponent *>(m_entityList.at(i));
		if (contComp != nullptr)
		{
			switch (key)
			{
			case SDLK_f:
				contComp->Shoot();
				break;
			}
		}
	}*/

	
}

void ControlSystem::fire()
{
	std::cout << "Im firing" << std::endl;
}

void ControlSystem::moveRight()
{

	
	std::vector<string> allowedTypes = { "Position" };
	for (auto &e : m_entityList)
	{
		auto comps = e->getComponentsOfType(allowedTypes);
		PositionComponent * posComp = dynamic_cast<PositionComponent *>(comps["Position"]);
		if (posComp != nullptr)
		{
			posComp->setPosition(posComp->getPosition() + SdlVector(1, 0));
		}
	}
}

void ControlSystem::moveLeft()
{
	std::vector<string> allowedTypes = { "Position" };
	for (auto &e : m_entityList)
	{
		auto comps = e->getComponentsOfType(allowedTypes);
		PositionComponent * posComp = dynamic_cast<PositionComponent *>(comps["Position"]);
		if (posComp != nullptr)
		{
			posComp->setPosition(posComp->getPosition() + SdlVector(-1, 0));
		}
	}
}
