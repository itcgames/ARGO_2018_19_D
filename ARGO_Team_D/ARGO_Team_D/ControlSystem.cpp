#include "ControlSystem.h"

ControlSystem::ControlSystem()
{
}

ControlSystem::~ControlSystem()
{
}

void ControlSystem::update()
{
	std::vector<string> allowedTypes = { "Body" };
	for (auto &e : m_entityList)
	{
		auto comps = e->getComponentsOfType(allowedTypes);
		BodyComponent * posComp = dynamic_cast<PositionComponent *>(comps["Position"]);
		if (posComp != nullptr)
		{
			posComp->setPosition(posComp->getPosition() + VectorAPI(1, 0));
		}
	}
}

void ControlSystem::moveRight()
{
	m_moveRight = true;
}

void ControlSystem::moveLeft()
{
	m_moveLeft = true;
}

void ControlSystem::jump()
{
	m_jump = true;
}

void ControlSystem::fire()
{
	std::cout << "I'm firing" << std::endl;
}
