#pragma once
#include"Command.h"
#include"ConcreteCommand.h"
#include"SDL.h"
#include<vector>
#include"ControlSystem.h"
class InputHandler {
public:
	InputHandler(ControlSystem & system);
	void handleInput(SDL_Keycode keycode);

	void bindButtonA();
	void bindButtonB();
private:
	Command * Move;
	Command * Fire;

	std::vector<Command *> commands;
	ControlSystem & m_controlSystem;
};