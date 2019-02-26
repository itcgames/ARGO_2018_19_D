#include "PlayerAiSystem.h"

PlayerAiSystem::PlayerAiSystem(BulletManager * manager) : m_bulletManager(manager)
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
	m_comp->m_sequences[0].addChildren({ &m_comp->m_sequences[1], new Jump(c->m_entity) });
	m_comp->m_sequences[1].addChildren({ new WalkRight(c->m_entity), new Shoot(c->m_entity, m_bulletManager) });

	//Right sub tree

}

void PlayerAiSystem::runTree()
{
	for (auto aiComp : m_comps) {
		if (aiComp->m_tree.run()) {
		}
		else {
			std::cout << "Behaviour tree exited with FAILURE" << std::endl;
		}
	}
}

void PlayerAiSystem::update()
{
	runTree();
}
