#ifndef PLAYERAISYSTEM_H
#define PLAYERAISYSTEM_H

#include "../ECS/Systems/System.h"
#include "PlayerAiComponent.h"
#include "Actions.h"
#include "..//Bullets/BulletManager.h"

class PlayerAiSystem : public System {
public:
	PlayerAiSystem(BulletManager* manager);
	void addComponent(PlayerAiComponent * c);
	void createTree(PlayerAiComponent * c);
	void runTree();
	void update();

private:
	vector<PlayerAiComponent*> m_comps;
	BulletManager* m_bulletManager;
};
#endif
