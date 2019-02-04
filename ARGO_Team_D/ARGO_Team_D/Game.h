#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL.h>
#include "Entities/Entities.h"
#include "Components/Components.h"
#include "Systems/RenderSystem.h"

using namespace std;

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
	void initialiseEntitys();
	void initialiseComponents();
	void initialiseSystems();
	void setUpFont();
	void quit();

	SDL_Window * p_window;
	SDL_Renderer * m_renderer;
	bool m_quit = false;

	int m_windowWidth = 1920;
	int m_windowHeight = 1080;
	TTF_Font* Sans;

	RenderSystem m_renderSystem;
};
#endif // !GAME_H