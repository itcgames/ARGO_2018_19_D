#ifndef ANIMATIONSTATE_H
#define ANIMATIONSTATE_H

#include "Animation.h"

class Animation;

class AnimationState {
public:
	virtual ~AnimationState() {};
	virtual void onEntry(Animation * a) = 0;
	virtual void onExit(Animation * a) = 0;
	virtual AnimationState * handle(Animation * a, AnimationState*s) = 0;
};

#endif //!ANIMATIONSTATE_H