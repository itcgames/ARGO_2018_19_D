#include "InputHandler.h"

InputHandler::InputHandler(ControlSystem & system):
	m_controlSystem{ system }
{
	m_moveRight = new MoveRightCommand(m_controlSystem);
	m_moveLeft = new MoveLeftCommand(m_controlSystem);
	m_fire = new FireCommand(m_controlSystem);
}

void InputHandler::handleInput(SDL_Event theEvent)
{
	switch (theEvent.type) 
	{
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
		m_moveRight->execute();
	}
	if (leftPressed)
	{
		m_moveLeft->execute();
	}
}
