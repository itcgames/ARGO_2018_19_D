#include "InputHandler.h"

InputHandler::InputHandler(ControlSystem & system, SDL_Joystick& controller, SDL_Haptic& haptic):
	m_controlSystem{ system }
{
	gGameController = &controller;
	gControllerHaptic = &haptic;
	m_moveRight = new MoveRightCommand(m_controlSystem);
	m_moveLeft = new MoveLeftCommand(m_controlSystem);
	m_fire = new FireCommand(m_controlSystem);
	m_jump = new JumpCommand(m_controlSystem);
}

void InputHandler::handleKeyboardInput(SDL_Event theEvent)
{
	switch (theEvent.type) 
	{
	case SDL_KEYDOWN:
		if (theEvent.key.keysym.sym ==  SDLK_RIGHT || theEvent.key.keysym.sym == SDLK_d)
		{
			m_rightPressed = true;
		}
		if (theEvent.key.keysym.sym == SDLK_LEFT || theEvent.key.keysym.sym == SDLK_a)
		{
			m_leftPressed = true;
		}
		if (theEvent.key.keysym.sym == SDLK_UP || theEvent.key.keysym.sym == SDLK_w)
		{
			m_upPressed = true;
		}
		break;

	case SDL_KEYUP:
		if (theEvent.key.keysym.sym == SDLK_RIGHT || theEvent.key.keysym.sym == SDLK_d)
		{
			m_rightPressed = false;
		}
		if (theEvent.key.keysym.sym == SDLK_LEFT || theEvent.key.keysym.sym == SDLK_a)
		{
			m_leftPressed = false;
		}
		if (theEvent.key.keysym.sym == SDLK_UP || theEvent.key.keysym.sym == SDLK_w)
		{
			m_upPressed = false;
		}
		break;
	}
}

void InputHandler::handleControllerInput(SDL_Event theEvent)
{
	switch (theEvent.type)
	{
	case SDL_JOYBUTTONDOWN:
		//Play rumble at 75% strenght for 500 milliseconds
		//SDL_HapticRumblePlay(gControllerHaptic, 0.75, 500);

		switch (theEvent.jbutton.button)
		{
		case 0:
			cout << "A button" << endl;
			break;
		case 1:
			cout << "B button" << endl;
			break;
		case 2:
			cout << "X button" << endl;
			break;
		case 3:
			cout << "Y button" << endl;
			break;
		case 4:
			cout << "LB button" << endl;
			break;
		case 5:
			cout << "RB button" << endl;
			break;
		case 6:
			cout << "Back button" << endl;
			break;
		case 7:
			cout << "Pause button" << endl;
			break;
		case 8:
			cout << "Left Bumper button" << endl;
			break;
		case 9:
			cout << "Right Bumper button" << endl;
			break;
		default:
			break;
		}
		break;

	case SDL_JOYAXISMOTION:
		if (theEvent.jaxis.which == 0)
		{
			//X axis motion
			if (theEvent.jaxis.axis == 0)
			{
				//Left of dead zone
				if (theEvent.jaxis.value < -JOYSTICK_DEAD_ZONE)
				{
					m_leftPressed = true;
				}
				//Right of dead zone
				else if (theEvent.jaxis.value > JOYSTICK_DEAD_ZONE)
				{
					m_rightPressed = true;
				}
				else
				{
					//xDir = 0;
					m_rightPressed = false;
					m_leftPressed = false;
				}
			}
			//Y axis motion
			else if (theEvent.jaxis.axis == 1)
			{
				//Below of dead zone
				if (theEvent.jaxis.value < -JOYSTICK_DEAD_ZONE)
				{
					cout << "Up" << endl;
				}
				//Above of dead zone
				else if (theEvent.jaxis.value > JOYSTICK_DEAD_ZONE)
				{
					cout << "Down" << endl;
				}
				else
				{
					//yDir = 0;
				}
			}

			//triggers
			if (theEvent.jaxis.axis == 5)
			{
				if (theEvent.jaxis.value > TRIGGER_DEAD_ZONE)
				{
					SDL_HapticRumblePlay(gControllerHaptic, 1.0, UINT32_MAX);
					m_ctrlPressed = true;
				}
				else
				{
					SDL_HapticRumbleStop(gControllerHaptic);
					m_ctrlPressed = false;
				}
				
			}
			else if (theEvent.jaxis.axis == 2)
			{
				cout << "Left Trigger: " << theEvent.jaxis.value << endl;
			}
		}
		break;
	}
}

void InputHandler::update()
{
	if (m_rightPressed)
	{
		m_moveRight->execute();
		//std::cout << "Moving Right" << std::endl;
	}
	if (m_leftPressed)
	{
		m_moveLeft->execute();
		//std::cout << "Moving Left" << std::endl;
	}
	if (m_ctrlPressed)
	{
		m_fire->execute();
		//std::cout << "Firing" << std::endl;
	}
	if (m_upPressed)
	{
		m_jump->execute();
		std::cout << "Jumping" << std::endl;
	}
}
