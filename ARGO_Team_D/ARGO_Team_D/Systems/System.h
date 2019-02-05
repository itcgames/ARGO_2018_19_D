#ifndef SYSTEM_H
#define SYSTEM_H

#include "..//Entities/Entities.h"

/// <summary>
/// Base System class.
/// </summary>
class System {
public:
	void addEntity(Entity * en) { m_entityList.push_back(en); }

protected:
	vector<Entity*> m_entityList;
};

#endif // !RENDERSYSTEM

