#pragma once
#include"Command.h"
#include"ConcreteCommand.h"
#include"SDL.h"
#include<vector>
#include"MacroCommand.h"
class InputHandler {
public:
	InputHandler();
	void handleInput(SDL_Keycode keycode);

	void bindButtonX();
	void bindButtonY();
	void bindButtonA();
	void bindButtonB();
	void bindButtonW();
private:
	Command * ButtonX;
	Command * ButtonY;
	Command * ButtonA;
	Command * ButtonB;
	Command * ButtonW;

	std::vector<Command *> commands;
	MacroCommand macro;
};