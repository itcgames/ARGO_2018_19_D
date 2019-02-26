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
	}
	~PlayerAiComponent() {}

	BehaviourTree m_tree;
	BehaviourTree::Selector m_selectors[1];
	BehaviourTree::Sequence m_sequences[2];
	BehaviourTree::Succeeder m_succeeders[1];
	Entity * m_entity;
	Enemy * m_nearestEnemy;
};
#endif
