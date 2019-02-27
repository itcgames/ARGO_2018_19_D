#ifndef HEALTHSYSTEM_H
#define HEALTHSYSTEM_H

#include "../ECS/Systems/System.h"
#include "../ECS/Components/BodyComponent.h"
#include "../ECS/Components/HealthComponent.h"

struct HealthComponents
{
	HealthComponent * health;
	BodyComponent * body;
};

class HealthSystem : public System
{
public:
	HealthSystem();
	~HealthSystem();
	void addEntity(Entity * e) override;
	void update();
	void removeEntity(const int id) override;
	bool playerAlive();
	void setPlayerAliveStatus(bool status);
	void reset();
private:
	std::map<int, HealthComponents> m_components;
	bool m_playerAlive;
};

#endif // !HEALTHSYSTEM_H
