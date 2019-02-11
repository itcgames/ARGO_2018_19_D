#ifndef IDLESTATE_H
#define IDLESTATE_H

#include "AnimationState.h"

class IdleState : public AnimationState {
public:
	IdleState() {};
	~IdleState() {};

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

#endif //!IDLESTATE_H