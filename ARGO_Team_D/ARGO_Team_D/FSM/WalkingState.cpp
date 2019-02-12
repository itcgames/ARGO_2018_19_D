#include "WalkingState.h"
#include "IdleState.h"

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

AnimationState * WalkingState::handle(Animation * a, SDL_Event & e)
{
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		default:
			return new IdleState();
			break;
		}
	}
}
