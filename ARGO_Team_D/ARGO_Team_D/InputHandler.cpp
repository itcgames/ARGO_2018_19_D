#include "InputHandler.h"

InputHandler::InputHandler()
{
	bindButtonA();
	bindButtonB();
	bindButtonW();
	bindButtonX();
	bindButtonY();

	macro = MacroCommand();
	macro.add(ButtonX);
	macro.add(ButtonX);
	macro.add(ButtonX);
	macro.add(ButtonA);
	macro.add(ButtonA);
	macro.add(ButtonY);
}

void InputHandler::handleInput(SDL_Keycode keycode)
{
	switch (keycode)
	{
	case SDLK_a:
		ButtonA->execute();
		commands.push_back(ButtonA);
		break;
	case SDLK_b:
		ButtonB->execute();
		commands.push_back(ButtonB);
		break;
	case SDLK_x:
		ButtonX->execute();
		commands.push_back(ButtonX);
		break;
	case SDLK_y:
		ButtonY->execute();
		commands.push_back(ButtonY);
		break;
	case SDLK_w:
		ButtonW->execute();
		commands.push_back(ButtonW);
		break;
	case SDLK_r:
		for (int i = 0; i < commands.size(); i++)
		{
			commands.at(i)->undo();
		}
		macro.undo();
		commands.clear();
		macro.removeAll();

		break;
	case SDLK_k:
		macro.execute();
		break;
	default:
		break;
	}

}

void InputHandler::bindButtonX()
{
	ButtonX = new FireCommand();
}

void InputHandler::bindButtonY()
{
	ButtonY = new CrouchCommand();
}

void InputHandler::bindButtonA()
{
	ButtonA = new JumpCommand();
}

void InputHandler::bindButtonB()
{
	ButtonB = new ShieldCommand();
}

void InputHandler::bindButtonW()
{
	ButtonW = new CrouchCommand();
}
