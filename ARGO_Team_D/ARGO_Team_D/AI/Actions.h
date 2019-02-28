#ifndef ACTIONS_H
#define ACTIONS_H

#include "BehaviourTree.h"
#include "../ECS/Entities/Entity.h"
#include "../Bullets/BulletManager.h"
#include "../Utils/VectorAPI.h"
#include "../Factories/EnemyFactory.h"
#include "../Observers/levelObserver.h"

class Action : public BehaviourTree::Node
{
public:
	Action(Entity * e) :
		m_entity(e)
	{
		if (m_entity->checkForComponent("Body")) {
			m_body = dynamic_cast<BodyComponent*>(m_entity->getComponent("Body"));
		}

		if (m_entity->checkForComponent("PlayerAi")) {
			m_Ai = dynamic_cast<PlayerAiComponent*>(m_entity->getComponent("PlayerAi"));
		}

		if (m_entity->checkForComponent("Sprite")) {
			m_Sprite = dynamic_cast<SpriteComponent*>(m_entity->getComponent("Sprite"));
		}

		if (m_entity->checkForComponent("Position")) {
			m_position = dynamic_cast<PositionComponent*>(m_entity->getComponent("Position"));
		}

		rifle = Mix_LoadWAV("ASSETS/SOUNDS/AssaultRifle.wav");
		Mix_VolumeChunk(rifle, 128 / 8);

		jumpSound = Mix_LoadWAV("ASSETS/SOUNDS/jump.wav");
		Mix_VolumeChunk(jumpSound, 128 / 4);
	}

	virtual bool run() = 0;
	Entity * m_entity;
	BodyComponent * m_body;
	PlayerAiComponent* m_Ai;
	SpriteComponent* m_Sprite;
	PositionComponent* m_position;
	Mix_Chunk * rifle = NULL;
	Mix_Chunk * jumpSound = NULL;
	bool playSound = false;
};

class WalkLeft : public Action
{
public:
	WalkLeft(Entity * e) :
		Action(e)
	{
	}

	bool run() override
	{
		if (!m_Ai->m_fighting || m_Ai->m_nearestEnemy->ai->getType() == 1) {
			b2Body * b2Body = m_body->getBody();
			b2Vec2 currentVelocity = b2Body->GetLinearVelocity();

			b2Body->SetLinearVelocity(b2Vec2(-15, currentVelocity.y));
			currentVelocity.x = -15;
			m_Ai->m_dir = -1;
			m_Sprite->m_flip = SDL_FLIP_HORIZONTAL;
		}
		return true;
	}
};

class WalkRight : public Action
{
public:
	WalkRight(Entity * e)
		: Action(e)
	{

	}

	bool run() override
	{
		if (!m_Ai->m_fighting) {
			b2Body * b2Body = m_body->getBody();
			b2Vec2 currentVelocity = b2Body->GetLinearVelocity();

			b2Body->SetLinearVelocity(b2Vec2(15, currentVelocity.y));
			currentVelocity.x = 15;
			m_Ai->m_dir = 1;
			m_Sprite->m_flip = SDL_FLIP_NONE;
		}
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

		if (m_body->isOnGround() && !m_body->isAiRightContact() && !m_Ai->m_fighting) {
			b2Body->SetLinearVelocity(b2Vec2(currentVelocity.x, -35));
			currentVelocity.y = -35;

			if(Mix_PlayChannel(-1, jumpSound, 0) == -1)
			{
				//return 1;
			}

			return true;
		}

		if (m_body->isOnGround() && m_Ai->m_nearestEnemy->ai->getType() == 1 && m_Ai->m_fighting) {
			b2Body->SetLinearVelocity(b2Vec2(currentVelocity.x, -35));
			currentVelocity.y = -35;

			if(Mix_PlayChannel(-1, jumpSound, 0) == -1)
			{
				//return 1;
			}

			return true;
		}

		if (m_body->isOnGround() && m_body->isRightContact()) {
			b2Body->SetLinearVelocity(b2Vec2(currentVelocity.x, -35));
			currentVelocity.y = -35;

			if(Mix_PlayChannel(-1, jumpSound, 0) == -1)
			{
				//return 1;
			}

			return true;
		}

		if (m_body->isOnGround() && m_body->isLeftContact()) {
			b2Body->SetLinearVelocity(b2Vec2(currentVelocity.x, -35));
			currentVelocity.y = -35;

			if(Mix_PlayChannel(-1, jumpSound, 0) == -1)
			{
				//return 1;
			}

			return true;
		}

		return true;
	}
};

class Shoot : public Action
{
public:
	Shoot(Entity * e, BulletManager* manager)
		: Action(e),
		m_manager(manager)
	{
	}

	bool run() override
	{
		if (CURRENTTIME >= MAXTIME && m_Ai->m_fighting) {
			b2Body * b2Body = m_body->getBody();
			b2Vec2 currentVelocity = b2Body->GetLinearVelocity();

			m_manager->createBullet(VectorAPI((b2Body->GetPosition().x * 30.0f) + (25 * m_Ai->m_dir), b2Body->GetPosition().y * 30.0f), 50 * m_Ai->m_dir, true);

			CURRENTTIME = 0;
			return true;
		}

		CURRENTTIME += 1;
		return true;
	}

private:
	BulletManager * m_manager;
	uint32 MAXTIME = 7;
	uint32 CURRENTTIME = 0;
};

class GoToNearest : public Action
{
public:
	GoToNearest(Entity * e, std::vector<Enemy*> ens, LevelObserver * m_obs)
		: Action(e),
		m_enemies(ens),
		m_observer(m_obs)
	{
	}

	bool run() override
	{
		Enemy* closest = nullptr;
		float dist = 0;
		float closestDist = 1000000;
		for (Enemy* en : m_enemies) {
			if (en->ai->getActivationState()) {
				dist = sqrt(((m_body->getBody()->GetPosition().x - en->body->getBody()->GetPosition().x) * (m_body->getBody()->GetPosition().x - en->body->getBody()->GetPosition().x))
					+ ((m_body->getBody()->GetPosition().y - en->body->getBody()->GetPosition().y) * (m_body->getBody()->GetPosition().y - en->body->getBody()->GetPosition().y)));

				if (dist < closestDist) {
					closestDist = dist;
					closest = en;
				}
			}
		}


		if (closest == nullptr && m_observer->getComplete()) {
			return true;
		}

		if (closest != nullptr) {
			m_Ai->m_nearestEnemy = closest;
			return true;
		}
		else
		{
			return false;
		}
	}

private:
	std::vector<Enemy*> m_enemies;
	LevelObserver * m_observer;
};

class IsEnemyRight : public Action
{
public:
	IsEnemyRight(Entity * e)
		: Action(e)
	{
	}

	bool run() override
	{
		if (m_Ai->m_nearestEnemy->position->getPosition().x > m_position->getPosition().x + 110)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class CheckLevelComplete : public Action
{
public:
	CheckLevelComplete(Entity * e, LevelObserver * obs)
		: Action(e),
		m_observer(obs)
	{

	}

	bool run() override
	{
		if (m_observer->getComplete() && !m_Ai->m_fighting) {
			return true;
		}
		else
		{
			return false;
		}
	}

private:
	LevelObserver * m_observer;
};

class CheckInFightPos : public Action
{
public:
	CheckInFightPos(Entity * e)
		: Action(e)
	{

	}

	bool run() override
	{
		if (m_position->getPosition().y > m_Ai->m_nearestEnemy->position->getPosition().y - 132 &&
			m_position->getPosition().y < m_Ai->m_nearestEnemy->position->getPosition().y + 164) {
			return true;
		}
		else {
			return false;
		}
	}
};

class CheckPassEnemy : public Action
{
public:
	CheckPassEnemy(Entity * e)
		: Action(e)
	{

	}

	bool run() override
	{
		float dist = sqrt(((m_Ai->m_nearestEnemy->body->getBody()->GetPosition().x - m_body->getBody()->GetPosition().x) * (m_Ai->m_nearestEnemy->body->getBody()->GetPosition().x - m_body->getBody()->GetPosition().x))
			+ ((m_Ai->m_nearestEnemy->body->getBody()->GetPosition().y - m_body->getBody()->GetPosition().y) * (m_Ai->m_nearestEnemy->body->getBody()->GetPosition().y - m_body->getBody()->GetPosition().y)));

		if (dist < 5 && !m_body->isRightContact() && ((m_Ai->m_nearestEnemy->body->getBody()->GetPosition().x < m_body->getBody()->GetPosition().x && m_Ai->m_dir == -1) || (m_Ai->m_nearestEnemy->body->getBody()->GetPosition().x > m_body->getBody()->GetPosition().x && m_Ai->m_dir == 1))) {
			m_Ai->m_fighting = true;
			if (!playSound)
			{
				if (Mix_PlayChannel(5, rifle, -1) == -1)
				{
					//return 1;
				}
				playSound = true;
			}
			return true;
		}
		else {
			m_Ai->m_fighting = false;
			Mix_HaltChannel(5);
			playSound = false;
			return false;
		}
	}
};
#endif