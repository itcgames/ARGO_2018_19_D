#include "Animation.h"
#include "IdleState.h"


Animation::Animation()
{
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

void Animation::handle(AnimationState * s)
{
	AnimationState * state = m_current->handle(this, s);
}
