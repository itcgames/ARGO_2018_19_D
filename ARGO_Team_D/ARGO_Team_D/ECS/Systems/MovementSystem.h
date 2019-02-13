#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include"System.h"
#include"../Components/PositionComponent.h"
#include"../Components/VelocityComponent.h"
#include<iostream>
class MovementSystem : public System
{
public:
	MovementSystem();
	void update();
private:
	std::vector<std::string> allowedTypes;
};

#endif // !MOVEMENTSYSTEM_H

