#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include "Components.h"

/// <summary>
/// Health Component.
/// </summary>
class HealthComponent : public Component {
public:
	HealthComponent(int health) { id = "Health"; m_health = health; };

	int getHealth() { return m_health; };
	void setHealth(int health) { m_health = health; };

private:
	int m_health;

};

#endif // !HEALTHCOMPONENT_H
