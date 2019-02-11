#ifndef CONTROLSYSTEM
#define CONTROLSYSTEM

#include <SDL.h>
#include <iostream>
#include "ECS/Components/Components.h"
#include "ECS/Systems/System.h"
#include "ECS/Components/BodyComponent.h"
#include "Utils/VectorAPI.h"

class ControlSystem : public System {
public:
	ControlSystem();
	~ControlSystem();
	void update();
	void moveRight();
	void moveLeft();
	void jump();
	void fire();
private:
	bool m_moveRight;
	bool m_moveLeft;
	bool m_jump;
	bool m_fire;
};


#endif // !CONTROLSYSTEM
