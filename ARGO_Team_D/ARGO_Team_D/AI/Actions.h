#ifndef ACTIONS_H
#define ACTIONS_H

#include "BehaviourTree.h"
#include "../ECS/Entities/Entity.h"
#include "../ECS/Components/BodyComponent.h"

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
	}
	bool run() override
	{
		b2Body * b2Body = m_body->getBody();
		b2Vec2 currentVelocity = b2Body->GetLinearVelocity();

		std::cout << "Jumping" << std::endl;

		b2Body->SetLinearVelocity(b2Vec2(currentVelocity.x, -35));
		currentVelocity.y = -35;

		return true;
	}
};
#endif
