#include "PlayerAiSystem.h"

PlayerAiSystem::PlayerAiSystem(BulletManager * manager, LevelObserver* obs) : m_bulletManager(manager), m_obs(obs)
{
}

void PlayerAiSystem::addComponent(PlayerAiComponent * c)
{
	m_comps.push_back(c);
	createTree(c);
}

void PlayerAiSystem::createTree(PlayerAiComponent * c)
{
	PlayerAiComponent * m_comp = c;
	m_comp->m_tree.setRootChild(&m_comp->m_sequences[0]);

	//Left sub tree
	m_comp->m_sequences[0].addChildren({ &m_comp->m_selectors[1], &m_comp->m_sequences[3] });

	m_comp->m_selectors[1].addChildren({ new CheckLevelComplete(c->m_entity, m_obs), &m_comp->m_selectors[2] });
	m_comp->m_selectors[2].addChildren({ &m_comp->m_sequences[1], &m_comp->m_sequences[2]});
	m_comp->m_sequences[1].addChildren({ new GoToNearest(c->m_entity, m_enemiesList, m_obs), new IsEnemyRight(c->m_entity), new WalkRight(c->m_entity), &m_comp->m_succeeders[0], new Jump(c->m_entity)});
	m_comp->m_sequences[2].addChildren({ new WalkLeft(c->m_entity), new Jump(c->m_entity), &m_comp->m_sequences[4] });


	// Check if can fight and then shoot
	m_comp->m_succeeders[0].setChild({ &m_comp->m_sequences[4]});
	m_comp->m_sequences[4].addChildren({ &m_comp->m_sequences[5], new Shoot(c->m_entity, m_bulletManager)});
	m_comp->m_sequences[5].addChildren({ new GoToNearest(c->m_entity, m_enemiesList, m_obs), new CheckPassEnemy(c->m_entity), new CheckInFightPos(c->m_entity)});


	//Right sub tree
	m_comp->m_sequences[3].addChildren({ &m_comp->m_succeeders[0], &m_comp->m_succeeders[1], new CheckLevelComplete(c->m_entity, m_obs), new Jump(c->m_entity), new WalkRight(c->m_entity) });
	m_comp->m_succeeders[1].setChild({ &m_comp->m_selectors[3]});
	m_comp->m_selectors[3].addChildren({ &m_comp->m_sequences[6], &m_comp->m_sequences[7] });
	m_comp->m_sequences[6].addChildren({ new IsEnemyRight(c->m_entity), new WalkRight(c->m_entity), &m_comp->m_succeeders[0]});
	m_comp->m_sequences[7].addChildren({ new WalkLeft(c->m_entity), new Jump(c->m_entity), &m_comp->m_sequences[4] });
}

void PlayerAiSystem::runTree()
{
	for (auto aiComp : m_comps) {
		if (aiComp->m_tree.run()) {
		}
		else {
			//std::cout << "Behaviour tree exited with FAILURE" << std::endl;
		}
	}
}

void PlayerAiSystem::update()
{
	runTree();
}
