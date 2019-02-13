#include "ControlSystem.h"
#include "ECS/Components/AnimationComponent.h"

ControlSystem::ControlSystem()
{
}

ControlSystem::~ControlSystem()
{
}

void ControlSystem::addEntity(Entity * e)
{
	std::vector<std::string> allowedTypes{ "Body" , "Animation"};
	auto comps = e->getComponentsOfType(allowedTypes);
	if (comps.size() >= allowedTypes.size() - 1)
	{
		ControlComponents c;
		c.body = dynamic_cast<BodyComponent*>(comps["Body"]); 
		c.animation = dynamic_cast<AnimationComponent*>(comps["Animation"]);
		m_components.push_back(c);
		m_entityList.push_back(e);
	}
}

void ControlSystem::update()
{
	for (auto & cc : m_components)
	{
		BodyComponent * body = cc.body;
		if (body != nullptr)
		{
			b2Body * b2Body = body->getBody();
			b2Vec2 currentVelocity = b2Body->GetLinearVelocity();
			if (m_jump && body->isOnGround())
			{
				b2Body->SetLinearVelocity(b2Vec2(currentVelocity.x, -35));
				currentVelocity.y = -35;
			}
			if (m_moveRight)
			{
				b2Body->SetLinearVelocity(b2Vec2(15, currentVelocity.y));
				currentVelocity.x = 15;
			}
			else if (m_moveLeft)
			{
				b2Body->SetLinearVelocity(b2Vec2(-15, currentVelocity.y));
				currentVelocity.x = -15;
			}
			else
			{
				b2Body->SetLinearVelocity(b2Vec2(0, currentVelocity.y));
				currentVelocity.x = 0;
			}
			m_moveRight = false, m_moveLeft = false, m_jump = false, m_fire = false;
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
	m_fire = true;
}

void ControlSystem::processInput(SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN) {
		std::vector<string> allowedTypes = {"Body", "Animation" };
		for (auto & cc : m_components)
		{
			if (cc.animation)
				cc.animation->handleInput(event);
		}
	}
}
