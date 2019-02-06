#pragma once
#include"Command.h"
#include"ConcreteCommand.h"
#include"SDL.h"
#include<vector>
#include"ControlSystem.h"
class InputHandler {
public:
	InputHandler(ControlSystem & system);
	void handleInput(SDL_Event theEvent);
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
};