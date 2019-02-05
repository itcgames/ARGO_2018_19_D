#ifndef ENTITYS_H
#define ENTITYS_H

#include <vector>
#include <algorithm>
#include <SDL.h>
#include "../Components/Components.h"

using namespace std;

/// <summary>
/// innnterface for entities.
/// entitys shared variables
/// </summary>
class Entity {
public:
	int id;

	Entity() {};
	virtual ~Entity() {};

	void addComponent(Component c) { m_components.push_back(c); }
	void removeComponenet(Component c) {
		//m_components.erase(std::remove(m_components.begin(), m_components.end(), c), m_components.end());
	};
	vector<Component> getComponents() { return m_components; }


private:
	vector<Component> m_components;

protected:

};
#endif // !ENTITY_H