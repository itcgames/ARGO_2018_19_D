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

void ControlSystem::move()
{
	std::cout << "im moving" << std::endl;
}
