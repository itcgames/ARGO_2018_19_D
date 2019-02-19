#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include"System.h"
#include"../Components/PositionComponent.h"
#include"../Components/VelocityComponent.h"
#include<iostream>

struct MovementComponents {
	PositionComponent * position;
	VelocityComponent * velocity;
};
class MovementSystem : public System
{
public:
	MovementSystem();
	void update();
	void removeEntity(const int id) override;
private:
	std::vector<std::string> allowedTypes;
	std::map<int, MovementComponents> m_components;
};

#endif // !MOVEMENTSYSTEM_H

