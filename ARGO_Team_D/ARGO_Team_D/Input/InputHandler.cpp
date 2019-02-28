#include "InputHandler.h"

InputHandler::InputHandler(ControlSystem & system, SDL_Joystick& controller, SDL_Haptic& haptic, Camera * cam):
	m_controlSystem{ system }
{
	m_cam = cam;
	gGameController = &controller;
	gControllerHaptic = &haptic;
	m_moveRight = new MoveRightCommand(m_controlSystem);
	m_moveLeft = new MoveLeftCommand(m_controlSystem);
	m_fire = new FireCommand(m_controlSystem);
	m_jump = new JumpCommand(m_controlSystem);

	startTimer = SDL_GetTicks();

	rifle = Mix_LoadWAV("ASSETS/SOUNDS/AssaultRifle.wav");
	Mix_VolumeChunk(rifle, 128 / 8);
	
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
		if (theEvent.key.keysym.sym == SDLK_LCTRL || theEvent.key.keysym.sym == SDLK_LCTRL)
		{
			m_ctrlPressed = true;
			if (!playSound)
			{
				if (Mix_PlayChannel(5, rifle, -1) == -1)
				{
					//return 1;
				}
				playSound = true;
			}
			
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
		if (theEvent.key.keysym.sym == SDLK_LCTRL || theEvent.key.keysym.sym == SDLK_LCTRL)
		{
			m_ctrlPressed = false;
			Mix_HaltChannel(5);
			playSound = false;
		}
		break;
	}
}

void InputHandler::handleControllerInput(SDL_Event theEvent,bool vibrationOn)
{
	switch (theEvent.type)
	{
	case SDL_JOYBUTTONDOWN:
		//Play rumble at 75% strenght for 500 milliseconds
		//SDL_HapticRumblePlay(gControllerHaptic, 0.75, 500);

		switch (theEvent.jbutton.button)
		{
		case 0:
			//cout << "A button" << endl;
			m_upPressed = true;

			break;
		case 1:
			//cout << "B button" << endl;
			break;
		case 2:
			//cout << "X button" << endl;
			break;
		case 3:
			//cout << "Y button" << endl;
			break;
		case 4:
			//cout << "LB button" << endl;
			break;
		case 5:
			//cout << "RB button" << endl;
			break;
		case 6:
			//cout << "Back button" << endl;
			break;
		case 7:
			//cout << "Pause button" << endl;
			m_paused = true;
			break;
		case 8:
			//cout << "Left Bumper button" << endl;
			break;
		case 9:
			//cout << "Right Bumper button" << endl;
			break;
		default:
			break;
		}
		break;
	case SDL_JOYBUTTONUP:
		switch (theEvent.jbutton.button)
		{
		case 0:
			m_upPressed = false;
			break;
		case 1:
			//cout << "B button" << endl;
			break;
		case 2:
			//cout << "X button" << endl;
			break;
		case 3:
			//cout << "Y button" << endl;
			break;
		case 4:
			//cout << "LB button" << endl;
			break;
		case 5:
			//cout << "RB button" << endl;
			break;
		case 6:
			//cout << "Back button" << endl;
			break;
		case 7:
			//cout << "Pause button" << endl;
			m_paused = false;
			break;
		case 8:
			//cout << "Left Bumper button" << endl;
			break;
		case 9:
			//cout << "Right Bumper button" << endl;
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
					//cout << "Up" << endl;
				}
				//Above of dead zone
				else if (theEvent.jaxis.value > JOYSTICK_DEAD_ZONE)
				{
					//cout << "Down" << endl;
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
					if (vibrationOn)
					{
						SDL_HapticRumblePlay(gControllerHaptic, 0.5f, UINT32_MAX);
					}
					
					m_ctrlPressed = true;
					if (!playSound)
					{
						if (Mix_PlayChannel(5, rifle, -1) == -1)
						{
							//return 1;
						}
						playSound = true;
					}
				}
				else
				{
					if (vibrationOn)
					{
						SDL_HapticRumbleStop(gControllerHaptic);
					}
					m_cam->m_shaking = false;
					m_ctrlPressed = false;
					Mix_HaltChannel(5);
					playSound = false;
				}

			}
			else if (theEvent.jaxis.axis == 2)
			{
				//cout << "Left Trigger: " << theEvent.jaxis.value << endl;
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
	}
	if (m_leftPressed)
	{
		m_moveLeft->execute();
	}

	float time = (SDL_GetTicks() - startTimer) / 1000;
	if (0.1f <= time && m_ctrlPressed)
	{
		m_fire->execute();
		m_cam->m_shaking = true;
		startTimer = SDL_GetTicks();
	}
	else
	{
		m_cam->m_shaking = false;
	}

	if (m_upPressed)
	{
		m_jump->execute();
	}
}

bool InputHandler::isPaused()
{
	return m_paused;
}

void InputHandler::resetHandler()
{
	m_rightPressed = false;
	m_leftPressed = false;
	m_upPressed = false;
	m_ctrlPressed = false;
	Mix_HaltChannel(5);
	SDL_HapticRumbleStop(gControllerHaptic);
	//m_paused = false;
}
