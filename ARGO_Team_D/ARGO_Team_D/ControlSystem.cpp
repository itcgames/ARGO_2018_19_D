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
		BodyComponent * bodyComp = dynamic_cast<BodyComponent *>(comps["Body"]);
		if (bodyComp != nullptr)
		{
			b2Body * body = bodyComp->getBody();
			b2Vec2 currentVelocity = body->GetLinearVelocity();
			if (m_moveRight)
			{
				body->SetLinearVelocity(b2Vec2(15, currentVelocity.y));
			}
			else if (m_moveLeft)
			{
				body->SetLinearVelocity(b2Vec2(-15, currentVelocity.y));
			}
			else if (m_jump)
			{
				body->SetLinearVelocity(b2Vec2(currentVelocity.x, -35));
			}
			else
			{
				body->SetLinearVelocity(b2Vec2(0, currentVelocity.y));
			}
			m_moveRight = false, m_moveLeft = false, m_jump = false;
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
