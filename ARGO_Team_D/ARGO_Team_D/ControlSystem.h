#ifndef CONTROLSYSTEM
#define CONTROLSYSTEM

#include"ECS/Components/Components.h"
#include"ECS/Systems/System.h"
#include<SDL.h>
#include<iostream>
class ControlSystem : public System {
public:
	ControlSystem();
	~ControlSystem();
	//void updateComponent(Component * c);

	void handleInput(SDL_Keycode key);
	void fire();
	void move();
private:
};


#endif // !CONTROLSYSTEM


