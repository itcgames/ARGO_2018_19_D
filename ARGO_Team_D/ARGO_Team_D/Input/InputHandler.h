#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "Command.h"
#include "ConcreteCommand.h"
#include "SDL.h"
#include <vector>
#include "../ECS/Systems/ControlSystem.h"
#include "../Camera.h"

class InputHandler {
public:
	InputHandler(ControlSystem & system, SDL_Joystick& controller, SDL_Haptic& haptic, Camera * cam);
	void handleKeyboardInput(SDL_Event theEvent);
	void handleControllerInput(SDL_Event theEvent, bool vibrationOn);
	void update();
	bool isPaused();
	void resetHandler();
private:
	Command * m_moveRight;
	Command * m_moveLeft;
	Command * m_fire;
	Command * m_jump;

	ControlSystem & m_controlSystem;

	bool m_rightPressed = false;
	bool m_leftPressed = false;
	bool m_upPressed = false;
	bool m_ctrlPressed = false;

	bool m_paused = false;

	const int JOYSTICK_DEAD_ZONE = 16000;
	const int TRIGGER_DEAD_ZONE = 20000;
	SDL_Joystick* gGameController = NULL;
	SDL_Haptic* gControllerHaptic = NULL;

	float startTimer;

	Mix_Chunk * rifle = NULL;
	bool playSound = false;

	Camera * m_cam;
};

#endif // !INPUTHANDLER_H
