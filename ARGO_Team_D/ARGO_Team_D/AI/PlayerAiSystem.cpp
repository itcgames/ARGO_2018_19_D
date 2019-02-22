#include "PlayerAiSystem.h"

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
