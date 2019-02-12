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

AnimationState * IdleState::handle(Animation * a, SDL_Event & e)
{
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		case SDLK_RIGHT:
			std::cout << "Right" << std::endl;
			return new WalkingState();
			break;
		case SDLK_LEFT:
			std::cout << "Left" << std::endl;
			return new WalkingState();
			break;
		default:
			return this;
			break;
		}
	}
}