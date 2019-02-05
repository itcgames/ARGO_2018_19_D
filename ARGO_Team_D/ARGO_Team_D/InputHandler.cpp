#include "InputHandler.h"

InputHandler::InputHandler(ControlSystem & system):
	m_controlSystem{ system }
{
	bindButtonA();
	bindButtonB();
}

void InputHandler::handleInput(SDL_Keycode keycode)
{
	switch (keycode)
	{
	case SDLK_a:
		Move->execute();
		commands.push_back(Move);
		break;
	case SDLK_b:
		Fire->execute();
		commands.push_back(Fire);
		break;
	case SDLK_r:
		for (int i = 0; i < commands.size(); i++)
		{
			commands.at(i)->undo();
		}
		commands.clear();

		break;
	case SDLK_k:
		break;
	default:
		break;
	}

}

void InputHandler::bindButtonA()
{
	Move = new MoveCommand(m_controlSystem);
}

void InputHandler::bindButtonB()
{
	Fire = new FireCommand(m_controlSystem);
}
