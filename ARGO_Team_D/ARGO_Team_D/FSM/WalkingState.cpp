#include "WalkingState.h"
#include "IdleState.h"
#include <iostream>

WalkingState::WalkingState()
{
	m_name = "Walking";
}

WalkingState::~WalkingState()
{
}

void WalkingState::onEntry(Animation * a)
{
	a->setPrevious(a->getCurrent());
	a->setCurrent(this);
}

void WalkingState::onExit(Animation * a)
{
	a->setPrevious(this);
	a->setCurrent(a->getPrevious());
}

AnimationState * WalkingState::handle(Animation * a, std::string state)
{
	if ("Idle" == state)
	{
		return new IdleState();
	}
	return this;
}
