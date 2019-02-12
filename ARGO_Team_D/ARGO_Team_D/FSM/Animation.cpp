#include "Animation.h"
#include "IdleState.h"


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

void Animation::handle(SDL_Event & e)
{
	AnimationState * state = m_current->handle(this, e);
	if (nullptr != state) {
		state->onEntry(this);
	}
}
