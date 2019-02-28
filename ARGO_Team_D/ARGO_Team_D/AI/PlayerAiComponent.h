#ifndef PLAYERAICOMPONENT_H
#define PLAYERAICOMPONENT_H

#include "../ECS/Entities/Entity.h"
#include "../ECS/Components/Components.h"
#include "BehaviourTree.h"
#include "../Factories/EnemyFactory.h"

class PlayerAiComponent : public Component {
public:
	PlayerAiComponent(Entity * e) :
		m_entity(e)
	{
		id = "PlayerAi";
		m_dir = 1;
	}
	~PlayerAiComponent() {}

	BehaviourTree m_tree;
	BehaviourTree::Selector m_selectors[4];
	BehaviourTree::Sequence m_sequences[8];
	BehaviourTree::Succeeder m_succeeders[2];
	BehaviourTree::RandomSelector m_random;
	Entity * m_entity;
	Enemy * m_nearestEnemy;
	int m_dir = 1;
	bool m_fighting = false;
};
#endif
