#include "Game.h"

const float WORLD_SCALE = 30.f;

Game::Game() :
	m_gravity(0, 90.81f),
	m_world(m_gravity),
	m_camera(m_windowWidth, m_windowHeight),
	m_physicsSystem(WORLD_SCALE)
{
	if (m_client.init()) {
		cout << "Client Created" << endl;
	}

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
	//Check for joysticks
	if (SDL_NumJoysticks() < 1)
	{
		cout << ("No Joystick connected!\n") << std::endl;
	}
	else
	{
		//Load joystick
		gGameController = SDL_JoystickOpen(0);
		if (gGameController == NULL)
		{
			cout << ("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError()) << endl;
		}
		else
		{
			// Get controller haptic device
			gControllerHaptic = SDL_HapticOpenFromJoystick(gGameController);
			if (gControllerHaptic == NULL)
			{
				printf("Warning: Controller does not support haptics! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Get initialize rumble
				if (SDL_HapticRumbleInit(gControllerHaptic) < 0)
				{
					printf("Warning: Unable to initialize rumble! SDL Error: %s\n", SDL_GetError());
				}
			}

		}
	}

	p_window = SDL_CreateWindow("Argo Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_windowWidth, m_windowHeight, 0);
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

	initialiseFactories();
	initialiseEntities();
	initialiseSystems();
	setUpFont();

	level = new Level(m_world, WORLD_SCALE);
	inputHandler = new InputHandler(m_controlSystem, *gGameController, *gControllerHaptic);
	level->load("ASSETS/LEVELS/Level1.tmx", m_resourceManager);
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

void Game::processEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (m_gameState)
		{
		case Menu:
			m_menu->handleInput(event);
			break;
		case PlayScreen:
			inputHandler->handleKeyboardInput(event);
			inputHandler->handleControllerInput(event);
			break;
		case Options:
			m_options->handleInput(event);
			break;
		case Credits:
			m_credits->handleInput(event);
			break;
		case LevelSelect:
			m_levelSelect->handleInput(event);
			break;
		default:
			break;
		}

		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				m_quit = true;
			break;
		case SDL_QUIT:
			m_quit = true;
			break;
		default:
			m_camera.m_shaking = false;
			break;
		}
	}
}

void Game::update()
{
	parseNetworkData(m_client.processMessage(m_client.Receive()));

	switch (m_gameState)
	{
	case Menu:
		m_menu->update();
		break;
	case PlayScreen:
		if (doneFading) // dont update the game unless screen is done fading
		{
			m_controlSystem.update();
			m_world.Step(1 / 60.f, 10, 5); // Update the Box2d world
			m_physicsSystem.update(); 
			m_camera.update(VectorAPI(m_playerBody->getBody()->GetPosition().x * WORLD_SCALE, m_playerBody->getBody()->GetPosition().y * WORLD_SCALE), 0);
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
		m_renderSystem.render(m_renderer, m_camera);
		level->render(m_renderer, m_camera);
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
	SDL_HapticClose(gControllerHaptic);
	SDL_JoystickClose(gGameController);
	gGameController = NULL;
	gControllerHaptic = NULL;
	SDL_DestroyWindow(p_window);
	SDL_Quit();
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

/// <summary>
/// initialises entitys.
/// </summary>
void Game::initialiseEntities()
{
	// Init Player
	Entity * e = m_playerFactory->create(1, VectorAPI(150, 0));
	m_entityList.push_back(e);
	m_controlSystem.addEntity(e);
	m_player = e;
	m_playerBody = dynamic_cast<BodyComponent*>(e->getComponentsOfType({ "Body" })["Body"]);
}

/// <summary>
/// Adds entitys to systems.
/// </summary>
void Game::initialiseSystems()
{
	for (auto i : m_entityList) 
	{ 
		if (i->checkForComponent("Sprite"))
		{
			m_renderSystem.addEntity(i);
		}
		if (i->checkForComponent("Body"))
		{
			m_physicsSystem.addEntity(i);
		}
	}
}

void Game::initialiseFactories()
{
	std::string spriteName = "test";
	m_playerFactory = new PlayerFactory(spriteName, VectorAPI(64, 64), m_resourceManager, m_world, WORLD_SCALE);
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

int Game::test_haptic(SDL_Joystick * joystick) {
	SDL_Haptic *haptic;
	SDL_HapticEffect effect;
	int effect_id;

	// Open the device
	haptic = SDL_HapticOpenFromJoystick(joystick);
	if (haptic == NULL) return -1; // Most likely joystick isn't haptic

	// See if it can do sine waves
	//if ((SDL_HapticQuery(haptic) & SDL_HAPTIC_SINE) == 0) {
	//	SDL_HapticClose(haptic); // No sine effect
	//	return -1;
	//}

	// Create the effect
	SDL_memset(&effect, 0, sizeof(SDL_HapticEffect)); // 0 is safe default
	effect.type = SDL_HAPTIC_SINE;
	effect.periodic.direction.type = SDL_HAPTIC_POLAR; // Polar coordinates
	effect.periodic.direction.dir[0] = 18000; // Force comes from south
	effect.periodic.period = 1000; // 1000 ms
	effect.periodic.magnitude = 20000; // 20000/32767 strength
	effect.periodic.length = 5000; // 5 seconds long
	effect.periodic.attack_length = 1000; // Takes 1 second to get max strength
	effect.periodic.fade_length = 1000; // Takes 1 second to fade away

	// Upload the effect
	effect_id = SDL_HapticNewEffect(haptic, &effect);

	// Test the effect
	SDL_HapticRunEffect(haptic, effect_id, 1);
	SDL_Delay(5000); // Wait for the effect to finish

	// We destroy the effect, although closing the device also does this
	SDL_HapticDestroyEffect(haptic, effect_id);

	// Close the device
	SDL_HapticClose(haptic);

	return 0; // Success
}

void Game::parseNetworkData(std::map<std::string, int> parsedMessage)
{
	for (auto const& pair : parsedMessage) {

		auto key = pair.first;
		auto value = pair.second;

		if (key == "ID") {
			m_client.setID(value);
		}
	}
}
