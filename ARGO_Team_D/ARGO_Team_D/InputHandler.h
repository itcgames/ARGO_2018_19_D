#pragma once
#include"Command.h"
#include"ConcreteCommand.h"
#include"SDL.h"
#include<vector>
#include"ControlSystem.h"
class InputHandler {
public:
	InputHandler(ControlSystem & system, SDL_Joystick& controller, SDL_Haptic& haptic);
	void handleInput(SDL_Event theEvent);
	void handleJoyStick(SDL_Event theEvent);
	void update();
private:
	Command * MoveRight;
	Command * MoveLeft;
	Command * Fire;

	std::vector<Command *> commands;
	ControlSystem & m_controlSystem;

	bool rightPressed = false;
	bool leftPressed = false;
	bool upPressed = false;
	bool cntrlPressed = false;

	const int JOYSTICK_DEAD_ZONE = 16000;
	const int TRIGGER_DEAD_ZONE = 20000;
	SDL_Joystick* gGameController = NULL;
	SDL_Haptic* gControllerHaptic = NULL;
};