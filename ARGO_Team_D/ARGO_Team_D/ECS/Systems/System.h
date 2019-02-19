#ifndef SYSTEM_H
#define SYSTEM_H

#include "..//Entities/Entity.h"

/// <summary>
/// Base System class.
/// </summary>
class System {
public:
	virtual void addEntity(Entity * en) { m_entityList.push_back(en); }
	virtual void removeEntity(const int id) {};
protected:
	vector<Entity*> m_entityList;
};

#endif //!SYSTEM_H