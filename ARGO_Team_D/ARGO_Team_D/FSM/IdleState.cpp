#include "IdleState.h"
#include "WalkingState.h"
#include <iostream>

IdleState::IdleState()
{
	m_name = "Idle";
}

IdleState::~IdleState()
{
}

void IdleState::onEntry(Animation * a)
{
	a->setPrevious(a->getCurrent());
	a->setCurrent(this);
}

void IdleState::onExit(Animation * a)
{
	a->setPrevious(this);
	a->setCurrent(a->getPrevious());
}

AnimationState * IdleState::handle(Animation * a, std::string state)
{
	if ("Walking" == state)
	{
		return new WalkingState();
	}
	return this;
}