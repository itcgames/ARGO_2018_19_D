#ifndef ACTIONS_H
#define ACTIONS_H

#include "BehaviourTree.h"
#include "../ECS/Entities/Entity.h"
#include "../ECS/Components/BodyComponent.h"
#include "../Bullets/BulletManager.h"
#include "../Utils/VectorAPI.h"

class Action : public BehaviourTree::Node
{
public:
	Action(Entity * e) :
		m_entity(e)
	{}

	virtual bool run() = 0;
	Entity * m_entity;
	BodyComponent * m_body;
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

		b2Body * b2Body = m_body->getBody();
		b2Vec2 currentVelocity = b2Body->GetLinearVelocity();

		m_manager->createBullet(VectorAPI((b2Body->GetPosition().x * 30.0f) + 50, b2Body->GetPosition().y * 30.0f), 50, true);

		cout << b2Body->GetPosition().x * 30.0f << ", " << b2Body->GetPosition().y * 30.0f << endl;
		return true;
	}

private:
	BulletManager * m_manager;
};
#endif
