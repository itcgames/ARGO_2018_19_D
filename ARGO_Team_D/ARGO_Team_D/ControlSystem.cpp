#include "ControlSystem.h"
#include "ECS/Components/AnimationComponent.h"

ControlSystem::ControlSystem()
{
}

ControlSystem::~ControlSystem()
{
}

void ControlSystem::update()
{
	std::vector<string> allowedTypes = { "Body" , "Animation"};
	for (auto &e : m_entityList)
	{
		auto comps = e->getComponentsOfType(allowedTypes);
		BodyComponent * bodyComp = dynamic_cast<BodyComponent *>(comps["Body"]);
		AnimationComponent * aComp = dynamic_cast<AnimationComponent *>(comps["Animation"]);
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

void ControlSystem::processInput(SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN) {
		std::vector<string> allowedTypes = {"Animation" };
		for (auto &e : m_entityList)
		{
			auto comps = e->getComponentsOfType(allowedTypes);
			if (comps.size() == allowedTypes.size()) {
				AnimationComponent * aComp = dynamic_cast<AnimationComponent *>(comps["Animation"]);

				aComp->handleInput(event);
			}
		}
	}
}
