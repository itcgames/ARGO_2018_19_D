#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>
#include "Button.h"
#include "Label.h"
#include <vector>

class Screen {
public:
	Screen();
	void handleInput(SDL_Event theEvent);
	virtual void draw(); //draw
	virtual void update();//update
	bool itemSelected(); //item selected
protected:
	std::vector<Button *> m_buttons;
	std::vector<Label *> m_labels;

	SDL_Renderer * rend;
	SDL_Window * window;

	float m_width;
	float m_height;

	int m_selectedItem = 0;
	const int JOYSTICK_DEAD_ZONE = 16000;
	bool activateJoystick = false;
};

#endif // !SCREEN_H
