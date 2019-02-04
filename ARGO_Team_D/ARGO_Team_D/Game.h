#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL.h>
#include <tmxlite/Map.hpp>

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	void processEvents();
	void update();
	void render();
	void quit();

	SDL_Window * p_window;
	bool m_quit = false;
};

#endif // !GAME_H