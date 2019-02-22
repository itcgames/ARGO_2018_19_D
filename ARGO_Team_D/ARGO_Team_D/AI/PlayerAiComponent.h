#ifndef PLAYERAICOMPONENT_H
#define PLAYERAICOMPONENT_H

#include "../ECS/Entities/Entity.h"
#include "../ECS/Components/Components.h"
#include "BehaviourTree.h"

class PlayerAiComponent : public Component {
public:
	PlayerAiComponent(Entity * e) :
		m_entity(e)
	{

	}
	~PlayerAiComponent() {}

	BehaviourTree m_tree;
	BehaviourTree::Selector m_selectors[1];
	BehaviourTree::Sequence m_sequences[1];
	BehaviourTree::Succeeder m_succeeders[1];
	Entity * m_entity;
};
#endif
