#ifndef ANIMATIONSTATE_H
#define ANIMATIONSTATE_H

#include "Animation.h"
#include <SDL_events.h>
#include <string>

class Animation;

class AnimationState {
public:
	virtual ~AnimationState() {};
	virtual void onEntry(Animation * a) = 0;
	virtual void onExit(Animation * a) = 0;
	virtual AnimationState * handle(Animation * a, std::string state) = 0;
	std::string m_name;
};

#endif //!ANIMATIONSTATE_H