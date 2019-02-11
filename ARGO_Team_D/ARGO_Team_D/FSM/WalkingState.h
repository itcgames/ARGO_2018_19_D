#ifndef WAlKINGSTATE_H
#define WALKINGSTATE_H

#include "AnimationState.h"

class WalkingState : public AnimationState {
public:
	WalkingState() {};
	~WalkingState() {};

	void onEntry(Animation * a)  override {
		a->setPrevious(a->getCurrent());
		a->setCurrent(this);
	};
	void onExit(Animation * a)  override {
		a->setPrevious(this);
		a->setCurrent(a->getPrevious());
	};

	AnimationState * handle(Animation * a, AnimationState*s) override {

	}
};


#endif //!WALKINGSTATE_H