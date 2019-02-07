#include "Game.h"
#include <sstream>

#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/SpriteComponent.h"

Game::Game() : m_gravity(0, 90.81f),
m_world(m_gravity)
{
	// Box2D Test Code
	m_bodyDef1.position = b2Vec2(b1X + 50, b1Y + 50);
	m_bodyDef1.type = b2_staticBody;
	m_body1 = m_world.CreateBody(&m_bodyDef1);
	m_poly1.SetAsBox((50.f), (50.f));
	m_fixture1.density = 1.f;
	m_fixture1.friction = 0.1f;
	m_fixture1.restitution = 0.0f;
	m_fixture1.shape = &m_poly1;
	m_body1->CreateFixture(&m_fixture1);
	m_body1->SetFixedRotation(true);

	m_bodyDef2.position = b2Vec2(b2X + 32, b2Y + 32);
	m_bodyDef2.type = b2_dynamicBody;
	m_body2 = m_world.CreateBody(&m_bodyDef2);
	m_poly2.SetAsBox((50.f), (50.f));
	m_fixture2.density = 1.f;
	m_fixture2.friction = 0.1f;
	m_fixture2.restitution = 0.0f;
	m_fixture2.shape = &m_poly2;
	m_body2->CreateFixture(&m_fixture2);
	m_body2->SetFixedRotation(true);

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialise SDL" << std::endl;
	}

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

	if (IMG_Init(imgFlags) != imgFlags)
	{
		cout << "Error: " << IMG_GetError() << endl;
	}

	// Initialize SDL_mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		cout << "Error: " << "Audio Initalisation" << endl;
	}

	p_window = SDL_CreateWindow("Argo Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_windowWidth, m_windowHeight, 0);
	printf("Window Size(%d , %d)\n", m_windowWidth, m_windowHeight);
	m_renderer = SDL_CreateRenderer(p_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	m_transitionScreen.x = 0;
	m_transitionScreen.y = 0;
	m_transitionScreen.w = m_windowWidth;
	m_transitionScreen.h = m_windowHeight;

	m_transitionAlphaPercent = 0;

	fadeOff = false;
	fadeOn = false;
	doneFading = false;

	if (NULL == p_window)
	{
		std::cout << "Error: Could not create window" << std::endl;
	}

	m_resourceManager = new ResourceManager(m_renderer);

	while (!m_resourceManager->checkLoaded()) {
		cout << "Loading..." << endl;
	}

	texture = m_resourceManager->getImageResource("test");
	square = m_resourceManager->getImageResource("testsquare");

	m_testMusic = m_resourceManager->getSoundResource("test");
	/*if (Mix_PlayMusic(m_testMusic, -1) == -1)
	{
	}*/

	m_gameState = State::Menu;
	m_menu = new MainMenu(m_windowWidth, m_windowHeight, *this, m_renderer, p_window);
	m_options = new OptionsMenu(m_windowWidth, m_windowHeight, *this, m_renderer, p_window);
	m_credits = new CreditScreen(m_windowWidth, m_windowHeight, *this, m_renderer, p_window);
	m_levelSelect = new LevelSelectMenu(m_windowWidth, m_windowHeight, *this, m_renderer, p_window);

	initialiseEntitys();
	initialiseComponents();
	initialiseSystems();
	setUpFont();


	Entity * e = new Entity();
	e->addComponent(new PositionComponent(0, 0));
	std::string name = "test";
	e->addComponent(new SpriteComponent(name, *m_resourceManager, 1920, 1080));
	m_renderSystem.addEntity(e);
	m_controlSystem.addEntity(e);
	inputHandler = new InputHandler(m_controlSystem);
	level = new Level(m_world);
	level->load("ASSETS/LEVELS/Level1.tmx", m_resourceManager);
	SDL_Rect bounds = { 0,0, 1920, 1080 };
	m_camera.setBounds(bounds);
}

Game::~Game()
{
}

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

void Game::setGameState(State state)
{
	m_gameState = state;
}

void Game::fadeToState(State state)
{
	m_nextState = state;
	fadeOn = true;
	doneFading = false;
}

void Game::fade()
{
	if (fadeOn)
	{
		m_transitionAlphaPercent += 0.075;
		if (m_transitionAlphaPercent >= 1)
		{
			m_transitionAlphaPercent = 1;
			m_gameState = m_nextState;
			fadeOff = true;
			fadeOn = false;
		}

		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255 * m_transitionAlphaPercent);
		SDL_RenderFillRect(m_renderer, &m_transitionScreen);
	}

	if (fadeOff)
	{
		m_transitionAlphaPercent -= 0.075;
		if (m_transitionAlphaPercent <= 0)
		{
			m_transitionAlphaPercent = 0;
			fadeOff = false;
			doneFading = true;
		}

		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255 * m_transitionAlphaPercent);
		SDL_RenderFillRect(m_renderer, &m_transitionScreen);
	}
}

void Game::processEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{

		switch (m_gameState)
		{
		case Menu:
			m_menu->handleMouse(event);
			break;
		case PlayScreen:
			inputHandler->handleInput(event);
			break;
		case Options:
			m_options->handleMouse(event);
			break;
		case Credits:
			m_credits->handleMouse(event);
			break;
		case LevelSelect:
			m_levelSelect->handleMouse(event);
			break;
		default:
			break;
		}

		
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				m_quit = true;
			// Demo Code
			if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
			{
				m_body2->SetLinearVelocity(b2Vec2(100, 0));
			}
			if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
			{
				m_body2->SetLinearVelocity(b2Vec2(-100, 0));
			}
			if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
			{
				m_body2->SetLinearVelocity(b2Vec2(0, -100));
			}
			break;
		case SDL_QUIT:
			m_quit = true;
			break;
		}
	}
}

void Game::update()
{
	switch (m_gameState)
	{
	case Menu:
		m_menu->update();
		break;
	case PlayScreen:
		if (doneFading) // dont update the game unless screen is done fading
		{
			std::vector<std::string> s = { "Position" };
			auto comps = player.getComponentsOfType(s);
			PositionComponent * p = dynamic_cast<PositionComponent*>(comps["Position"]);
			m_camera.update(VectorAPI(m_body2->GetPosition().x, m_body2->GetPosition().y), 0);
			m_world.Step(1 / 60.f, 10, 5); // Update the Box2d world
			inputHandler->update();
		}
		break;
	case Options:
		m_options->update();
		break;
	case Credits:
		m_credits->update();
		break;
	case LevelSelect:
		m_levelSelect->update();
		break;
	default:
		break;
	}
	
}

void Game::render()
{
	const SDL_Rect bounds = m_camera.getBounds();
	if (m_renderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
	}

	SDL_SetRenderDrawColor(m_renderer, 125, 125, 125, 255);

	SDL_RenderClear(m_renderer);
	


	switch (m_gameState)
	{
	case Menu:
		m_menu->draw();
		break;
	case PlayScreen:
		m_renderSystem.render(m_renderer, bounds);

		level->render(m_renderer, bounds);

		b1X = m_body1->GetPosition().x - 50;
		b1Y = m_body1->GetPosition().y - 50;
		b2X = m_body2->GetPosition().x - 50;
		b2Y = m_body2->GetPosition().y - 50;

		SDL_Rect dest;
		dest.x = b1X - bounds.x;
		dest.y = b1Y - bounds.y;
		dest.w = 100.f;
		dest.h = 100.f;
		SDL_RenderCopy(m_renderer, square, NULL, &dest);

		SDL_Rect dest2;
		dest2.x = b2X - bounds.x;
		dest2.y = b2Y - bounds.y;
		dest2.w = 100.f;
		dest2.h = 100.f;
		SDL_RenderCopy(m_renderer, square, NULL, &dest2);

		
		break;
	case Options:
		m_options->draw();
		break;
	case Credits:
		m_credits->draw();
		break;
	case LevelSelect:
		m_levelSelect->draw();
		break;
	default:
		break;
	}

	fade();
	
	SDL_RenderPresent(m_renderer);
}

void Game::quit()
{
	Mix_CloseAudio();
	TTF_Quit();
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
