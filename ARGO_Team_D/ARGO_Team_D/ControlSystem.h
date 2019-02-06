#ifndef CONTROLSYSTEM
#define CONTROLSYSTEM

#include"ECS/Components/Components.h"
#include"ECS/Systems/System.h"
#include<SDL.h>
#include<iostream>
#include"ECS/Components/PositionComponent.h"
#include"SdlVector.h"
class ControlSystem : public System {
public:
	ControlSystem();
	~ControlSystem();
	//void updateComponent(Component * c);

	void handleInput(SDL_Keycode key);
	void fire();
	void moveRight();
	void moveLeft();
private:

};


#endif // !CONTROLSYSTEM
