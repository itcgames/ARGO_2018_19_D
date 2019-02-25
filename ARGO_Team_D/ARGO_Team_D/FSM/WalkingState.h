#ifndef WAlKINGSTATE_H
#define WALKINGSTATE_H

#include "AnimationState.h"

class WalkingState : public AnimationState {
public:
	WalkingState();
	~WalkingState();

	void onEntry(Animation * a)  override;
	void onExit(Animation * a)  override;

	AnimationState * handle(Animation * a, std::string state) override;
};

#endif //!WALKINGSTATE_H