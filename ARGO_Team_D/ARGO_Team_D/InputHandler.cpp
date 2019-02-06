#include "InputHandler.h"

InputHandler::InputHandler(ControlSystem & system):
	m_controlSystem{ system }
{
	MoveRight = new MoveRightCommand(m_controlSystem);
	MoveLeft = new MoveLeftCommand(m_controlSystem);
	Fire = new FireCommand(m_controlSystem);

}

void InputHandler::handleInput(SDL_Event theEvent)
{



	switch (theEvent.type) {
	case SDL_KEYDOWN:
		if (theEvent.key.keysym.sym ==  SDLK_RIGHT || theEvent.key.keysym.sym == SDLK_d)
		{
			rightPressed = true;
		}
		if (theEvent.key.keysym.sym == SDLK_LEFT || theEvent.key.keysym.sym == SDLK_a)
		{
			leftPressed = true;
		}
		break;

	case SDL_KEYUP:
		if (theEvent.key.keysym.sym == SDLK_RIGHT || theEvent.key.keysym.sym == SDLK_d)
		{
			rightPressed = false;
		}
		if (theEvent.key.keysym.sym == SDLK_LEFT || theEvent.key.keysym.sym == SDLK_a)
		{
			leftPressed = false;
		}
		break;
	}
}


void InputHandler::update()
{
	
	if (rightPressed)
	{
		MoveRight->execute();
	}
	if (leftPressed)
	{
		MoveLeft->execute();
	}
}
