#ifndef ACTIONS_H
#define ACTIONS_H

#include "BehaviourTree.h"
#include "../ECS/Entities/Entity.h"
#include "../ECS/Components/BodyComponent.h"
#include "../Bullets/BulletManager.h"
#include "../Utils/VectorAPI.h"
#include <time.h>
#include "../Factories/EnemyFactory.h"

class Action : public BehaviourTree::Node
{
public:
	Action(Entity * e) :
		m_entity(e)
	{}

	virtual bool run() = 0;
	Entity * m_entity;
	BodyComponent * m_body;
	PlayerAiComponent* m_Ai;
};

class WalkLeft : public Action
{
public:
	WalkLeft(Entity * e) :
		Action(e)
	{
		if (m_entity->checkForComponent("Body")) {
			m_body = dynamic_cast<BodyComponent*>(m_entity->getComponent("Body"));
		}
	}

	bool run() override
	{
		b2Body * b2Body = m_body->getBody();
		b2Vec2 currentVelocity = b2Body->GetLinearVelocity();

		std::cout << "Walking left" << std::endl;

		b2Body->SetLinearVelocity(b2Vec2(-15, currentVelocity.y));
		currentVelocity.x = -15;
		return true;
	}
};

class WalkRight : public Action
{
public:
	WalkRight(Entity * e)
		: Action(e)
	{
		if (m_entity->checkForComponent("Body")) {
			m_body = dynamic_cast<BodyComponent*>(m_entity->getComponent("Body"));
		}
	}

	bool run() override
	{
		b2Body * b2Body = m_body->getBody();
		b2Vec2 currentVelocity = b2Body->GetLinearVelocity();

		std::cout << "Walking right" << std::endl;

		b2Body->SetLinearVelocity(b2Vec2(15, currentVelocity.y));
		currentVelocity.x = 15;
		return true;
	}
};

class Jump : public Action
{
public:
	Jump(Entity * e)
		: Action(e)
	{
		if (m_entity->checkForComponent("Body")) {
			m_body = dynamic_cast<BodyComponent*>(m_entity->getComponent("Body"));
		}
	}
	bool run() override
	{
		b2Body * b2Body = m_body->getBody();
		b2Vec2 currentVelocity = b2Body->GetLinearVelocity();

		std::cout << "Jumping" << std::endl;

		if (m_body->isOnGround()) {
			b2Body->SetLinearVelocity(b2Vec2(currentVelocity.x, -30));
			currentVelocity.y = -30;

			return true;
		}

		return false;
	}
};

class Shoot : public Action
{
public:
	Shoot(Entity * e, BulletManager* manager)
		: Action(e), 
		m_manager(manager)
	{
		if (m_entity->checkForComponent("Body")) {
			m_body = dynamic_cast<BodyComponent*>(m_entity->getComponent("Body"));
		}
	}

	bool run() override
	{
		if (CURRENTTIME >= MAXTIME) {
			b2Body * b2Body = m_body->getBody();
			b2Vec2 currentVelocity = b2Body->GetLinearVelocity();


			m_manager->createBullet(VectorAPI((b2Body->GetPosition().x * 30.0f) + 50, b2Body->GetPosition().y * 30.0f), 50, true);

			CURRENTTIME = 0;
			return true;
		}

		CURRENTTIME += 1;
		return false;
	}

private:
	BulletManager * m_manager;
	uint32 MAXTIME = 5;
	uint32 CURRENTTIME = 0;
};

class GoToNearest : public Action
{
public:
	GoToNearest(Entity * e, std::vector<Enemy*> ens)
		: Action(e),
		m_enemies(ens)
	{
		if (m_entity->checkForComponent("Body")) {
			m_body = dynamic_cast<BodyComponent*>(m_entity->getComponent("Body"));
		}
	}

	bool run() override
	{
		Enemy* closest;
		float dist = 0;
		float closestDist = 1000000;
		for (Enemy* en : m_enemies) {
			if (closest != nullptr) {
				dist = sqrt(((closest->body->getBody()->GetPosition().x - en->body->getBody()->GetPosition().x) * (closest->body->getBody()->GetPosition().x - en->body->getBody()->GetPosition().x))
					+ ((closest->body->getBody()->GetPosition().y - en->body->getBody()->GetPosition().y) * (closest->body->getBody()->GetPosition().y - en->body->getBody()->GetPosition().y)));

				if (dist < closestDist) {
					closestDist = dist;
					closest = en;
				}
			}
			else
			{
				closest = en;
			}
		}

		if (m_entity->checkForComponent("PlayerAi")) {
			m_Ai = dynamic_cast<PlayerAiComponent*>(m_entity->getComponent("PlayerAi"));
		}

		if (closest != nullptr) {
			m_Ai->m_nearestEnemy = closest;
			return true;
		}
		else {
			return false;
		}
	}

private:
	std::vector<Enemy*> m_enemies;
};

class CheckLevelComplete : public Action
{
public:
	CheckLevelComplete(Entity * e)
		: Action(e)
	{

	}

	bool run() override
	{
	
	}

private:

};
#endif
