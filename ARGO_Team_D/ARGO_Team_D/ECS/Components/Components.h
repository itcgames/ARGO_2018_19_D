#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <utility>
#include <string>
#include "../../SdlVector.h"

/// <summary>
/// Component Interface
/// </summary>
class Component {
public:
	Component() {}
	virtual ~Component() {}
	std::string id;
protected:

};

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

/// <summary>
/// Position Component.
/// </summary>
class PositionComponent : public Component {
public:
	PositionComponent(const SdlVector & v) : m_position(v) {id = "Position"; };
	PositionComponent(float _x, float _y) : m_position(SdlVector(_x, _y)) { id = "Position"; };
	SdlVector getPosition() { return m_position; };
private:
	SdlVector m_position;
};

#endif // !COMPONENTS_H

