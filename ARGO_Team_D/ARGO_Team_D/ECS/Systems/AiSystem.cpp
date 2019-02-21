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
		m_components.insert(std::make_pair(e->id, aiComp));
		m_entityList.push_back(e);
	}
}

void AiSystem::update()
{
	for (auto & comp : m_components)
	{
		auto & ac = comp.second;

		auto body = ac.body->getBody();
		if (ac.body->getBulletHitCount() > 3)
		{
			ac.ai->setActivationState(false);
			ac.body->setBulletHitCount(0); // Reset bullet hit count
			body->SetTransform(b2Vec2(-1000, 0), body->GetAngle());
		}
		bool active = ac.ai->getActivationState();
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

void AiSystem::removeEntity(const int id)
{
	auto comp = m_components.find(id);
	if (comp != m_components.end()) {
		m_components.erase(comp);
	}
	m_entityList.erase(std::remove_if(m_entityList.begin(), m_entityList.end(), [id](Entity* en) {
		return en->id == id;
	}), m_entityList.end());
}
