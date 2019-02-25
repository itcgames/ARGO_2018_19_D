#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include "Components.h"

/// <summary>
/// Health Component.
/// </summary>
class HealthComponent : public Component {
public:
	HealthComponent(int health, int lives) { id = "Health"; m_health = health; m_lives = lives; };

	int getHealth() { return m_health; };
	void setHealth(int health) { m_health = health; };
	int getLives() { return m_lives; };
	void setLives(int lives) { m_lives = lives; };

private:
	int m_health;
	int m_lives;

};

#endif // !HEALTHCOMPONENT_H
