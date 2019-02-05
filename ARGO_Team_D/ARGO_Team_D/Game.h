#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdlib.h>
#include "Entities/Entities.h"
#include "Components/Components.h"
#include "Systems/RenderSystem.h"
#include <tmxlite/Map.hpp>
#include"InputHandler.h"

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

	InputHandler inputHandler;

	int m_windowWidth = 1920;
	int m_windowHeight = 1080;
	TTF_Font* Sans;

	RenderSystem m_renderSystem;
};
#endif // !GAME_H