#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdlib.h>
#include "ECS/Entities/Entity.h"
#include "ECS/Components/Components.h"
#include "ECS/Systems/RenderSystem.h"
#include <tmxlite/Map.hpp>
#include "InputHandler.h"
#include "Resource Manager/ResourceManager.h"

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

	InputHandler inputHandler;

	ResourceManager m_resourceManager;
	SDL_Surface* m_testLoad;
	SDL_Texture * texture;
	Mix_Music *	m_testMusic;

};
#endif // !GAME_H