#include "Animation.h"
#include "IdleState.h"
#include <iostream>


Animation::Animation()
{
	m_current = new IdleState();
	m_previous = m_current;
}

Animation::~Animation()
{
}

AnimationState * Animation::getCurrent()
{
	return m_current;
}

AnimationState * Animation::getPrevious()
{
	return m_previous;
}

void Animation::setCurrent(AnimationState * s)
{
	m_current = s;
}

void Animation::setPrevious(AnimationState * s)
{
	m_previous = s;
}

void Animation::handle(std::string newState)
{
	AnimationState * state = m_current->handle(this, newState);
	if (nullptr != state && state != m_current) {
		state->onEntry(this);
	}
}