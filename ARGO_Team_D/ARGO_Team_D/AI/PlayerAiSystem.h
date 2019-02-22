#ifndef PLAYERAISYSTEM_H
#define PLAYERAISYSTEM_H

#include "../ECS/Systems/System.h"
#include "PlayerAiComponent.h"

class PlayerAiSystem : public System {
public:
	void addComponent(PlayerAiComponent * c);
	void createTree(PlayerAiComponent * c);
	void runTree();
	void update();

private:
	vector<PlayerAiComponent*> m_comps;
};
#endif
