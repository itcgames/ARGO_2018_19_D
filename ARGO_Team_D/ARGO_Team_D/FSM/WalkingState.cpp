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
	std::cout << "Entry Walking" << std::endl;
	a->setPrevious(a->getCurrent());
	a->setCurrent(this);
}

void WalkingState::onExit(Animation * a)
{
	std::cout << "Exit Walking" << std::endl;
	a->setPrevious(this);
	a->setCurrent(a->getPrevious());
}

AnimationState * WalkingState::handle(Animation * a, SDL_Event & e)
{
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		case SDLK_d:
			return this;
		case SDLK_a:
			return this;
		case SDLK_LEFT:
			return this;
		case SDLK_RIGHT:
			return this;
		default:
			return new IdleState();
			break;
		}
	}
}
