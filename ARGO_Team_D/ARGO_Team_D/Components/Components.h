#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <utility>
#include <string>

/// <summary>
/// Component Interface
/// </summary>
class Component {
public:
	Component() {}
	virtual ~Component() {}

protected:
	string id = "";

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
	PositionComponent(std::pair<float, float> pos) : m_position(pos) { id = "Position";  m_start = pos; };

	std::pair<float, float> getPos() { return m_position; };
	void setPos(std::pair<float, float> pos) { m_position = pos; };
	void resetPos() { m_position = m_start; }

	std::string getPosStr() {
		return std::string("X: " + std::to_string(m_position.first) + "," + "Y: " + std::to_string(m_position.second));
	}

private:
	std::pair<float, float> m_position;
	std::pair<float, float> m_start;
};

#endif // !COMPONENTS_H

