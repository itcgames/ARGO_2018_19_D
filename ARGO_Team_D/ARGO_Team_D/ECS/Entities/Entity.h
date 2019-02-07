#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <algorithm>
#include <SDL.h>
#include "../Components/Components.h"
#include <map>
#include <algorithm>

using namespace std;

/// <summary>
/// innnterface for entities.
/// entitys shared variables
/// </summary>
class Entity {
public:
	int id;

	Entity(int id) {};
	virtual ~Entity() {};

	void addComponent(Component * c) { m_components.push_back(c); }
	void removeComponent(Component * c) {
		//m_components.erase(std::remove(m_components.begin(), m_components.end(), c), m_components.end());
	};
	vector<Component*> *getComponents() { return &m_components; }
	std::map<std::string, Component*> getComponentsOfType(const std::vector<std::string> & types) {
		std::map<std::string, Component*> compMap;
		for (auto & comp : m_components) {
			auto it = std::find(types.begin(), types.end(), comp->id);
			if (it != types.end()) {
				compMap.insert(std::make_pair(comp->id, comp));
			}
		}
		return compMap;
	};

	bool checkForComponent(const std::string type) {
		for (auto & comp : m_components) {
			if (comp->id == type)
			{
				return true;
			}
		}
		return false;
	}

private:
	vector<Component*> m_components;

protected:

};
#endif // !ENTITY_H

