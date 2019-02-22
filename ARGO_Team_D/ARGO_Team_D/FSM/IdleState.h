#ifndef IDLESTATE_H
#define IDLESTATE_H

#include "AnimationState.h"

class IdleState : public AnimationState {
public:
	IdleState();
	~IdleState();

	void onEntry(Animation * a)  override;
	void onExit(Animation * a)  override;

	AnimationState * handle(Animation * a, std::string state) override;
};

#endif //!IDLESTATE_H