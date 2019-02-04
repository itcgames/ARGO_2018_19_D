#include "Game.h"

Game::Game()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialise SDL" << std::endl;
	}

	p_window = SDL_CreateWindow("Argo Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_windowWidth, m_windowHeight, SDL_WINDOW_OPENGL);
	m_renderer = SDL_CreateRenderer(p_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (NULL == p_window)
	{
		std::cout << "Error: Could not create window" << std::endl;
	}

	initialiseEntitys();
	initialiseComponents();
	initialiseSystems();
	setUpFont();


}

Game::~Game() {}

void Game::run()
{
	bool exit = false;

	float timePerFrame = 1000.f / 60.f;
	Uint32 timeSinceLastUpdate = 0;
	Uint32 timeSinceStart = SDL_GetTicks();

	while (!m_quit)
	{
		processEvents();
		timeSinceLastUpdate += SDL_GetTicks() - timeSinceStart;
		timeSinceStart = SDL_GetTicks();

		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update();
		}
		render();
	}
	quit();
}

void Game::processEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				m_quit = true;
			break;
		case SDL_QUIT:
			m_quit = true;
			break;
		}
	}
}

void Game::update()
{
	// Empty ...
}

void Game::render()
{
	if (m_renderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
	}

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

	SDL_RenderClear(m_renderer);

	m_renderSystem.render(m_renderer);

	SDL_RenderPresent(m_renderer);
}

void Game::quit()
{
	SDL_DestroyWindow(p_window);
	SDL_Quit();
}

/// <summary>
/// initialises entitys.
/// </summary>
void Game::initialiseEntitys()
{

}

/// <summary>
/// adds components to entitys.
/// </summary>
void Game::initialiseComponents()
{
	
}

/// <summary>
/// Adds entitys to systems.
/// </summary>
void Game::initialiseSystems()
{
	
}

/// <summary>
/// Sets up font for game.
/// </summary>
void Game::setUpFont() {

	if (TTF_Init() < 0)
	{
		std::cout << "error error error" << std::endl;
	}
	const char *path = "ASSETS\\FONTS\\arial.ttf";
	Sans = TTF_OpenFont(path, 50);
}

