#ifndef PLAYERAISYSTEM_H
#define PLAYERAISYSTEM_H

#include "../ECS/Systems/System.h"
#include "PlayerAiComponent.h"
#include "Actions.h"
#include "..//Bullets/BulletManager.h"
#include "../Factories/EnemyFactory.h"
#include "../Observers/levelObserver.h"

class PlayerAiSystem : public System {
public:
	PlayerAiSystem(BulletManager* manager, LevelObserver* obs);
	void addEnemy(Enemy* en) { m_enemiesList.push_back(en); }
	void addComponent(PlayerAiComponent * c);
	void createTree(PlayerAiComponent * c);
	void runTree();
	void update();

private:
	vector<PlayerAiComponent*> m_comps;
	BulletManager* m_bulletManager;
	vector<Enemy*> m_enemiesList;
	LevelObserver* m_obs;
};
#endif
