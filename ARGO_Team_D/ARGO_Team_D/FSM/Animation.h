#ifndef ANIMATION_H
#define ANIMATION_H

#include "AnimationState.h"
#include <SDL_events.h>
#include <string>

class AnimationState;

class Animation {
public:
	Animation();
	~Animation();

	AnimationState * getCurrent();
	AnimationState * getPrevious();
	void setCurrent(AnimationState * s);
	void setPrevious(AnimationState * s);
	void handle(std::string newState);
protected:
	AnimationState * m_current;
	AnimationState * m_previous;
};

#endif //!ANIMATION_H