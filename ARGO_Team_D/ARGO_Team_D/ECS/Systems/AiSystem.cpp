#include "AiSystem.h"

AiSystem::AiSystem(BodyComponent * playerBody, const float SCALE) 
	: m_playerBody(playerBody),
	WORLD_SCALE(SCALE)
{
	m_allowedTypes = { "Body", "Animation", "Ai", "Sprite" };
}

AiSystem::~AiSystem()
{
}

void AiSystem::addEntity(Entity * e)
{
	auto comps = e->getComponentsOfType(m_allowedTypes);
	if (comps.size() >= m_allowedTypes.size() - 1)
	{
		AiComponents aiComp;
		aiComp.body = dynamic_cast<BodyComponent*>(comps["Body"]);
		aiComp.animation = dynamic_cast<AnimationComponent*>(comps["Animation"]);
		aiComp.ai = dynamic_cast<AiComponent*>(comps["Ai"]);
		aiComp.sprite = dynamic_cast<SpriteComponent*>(comps["Sprite"]);
		m_components.push_back(aiComp);
		m_entityList.push_back(e);
	}
}

void AiSystem::update()
{
	for (auto & ac : m_components)
	{
		bool active = ac.ai->getActivationState();
		auto body = ac.body->getBody();
		ac.sprite->setRender(active);
		if (active)
		{
			auto body = ac.body->getBody();
			auto bodyPos = body->GetPosition();
			auto bodyVel = body->GetLinearVelocity();
			int minX = ac.ai->getMinX();
			int maxX = ac.ai->getMaxX();
			int direction = ac.ai->getDirection();
			if(direction < 0)
			{
				if ((bodyPos.x ) > minX / WORLD_SCALE)
				{
					body->SetLinearVelocity(b2Vec2(-10, bodyVel.y));
				}
				else
				{
					ac.ai->setDirection(-direction);
				}
			}
			else if(direction > 0)
			{
				if ((bodyPos.x) < maxX / WORLD_SCALE)
				{
					body->SetLinearVelocity(b2Vec2(10, bodyVel.y));
				}
				else
				{
					ac.ai->setDirection(-direction);
				}
			}
		}
		else
		{
			body->SetLinearVelocity(b2Vec2(0, 0));
		}
	}
}