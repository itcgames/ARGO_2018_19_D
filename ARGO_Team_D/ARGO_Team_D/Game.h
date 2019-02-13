#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "ECS/Entities/Entity.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/PhysicsSystem.h"
#include "ECS/Systems/AnimationSystem.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/SpriteComponent.h"
#include <tmxlite/Map.hpp>
#include "InputHandler.h"
#include "Resource Manager/ResourceManager.h"
#include "ControlSystem.h"
#include <Box2D\Box2D.h>
#include "Level/Level.h"
#include "Factories/Factory.h"
#include "Factories/PlayerFactory.h"
#include "Menu/Button.h"
#include "Menu/MainMenu.h"
#include "Menu/OptionsMenu.h"
#include "Menu/CreditsScreen.h"
#include "Menu/LevelSelectMenu.h"
#include "Utils/VectorAPI.h"
#include "Camera.h"
#include <SDL_haptic.h>
#include "ECS/Systems/NetworkingSystem.h"

class MainMenu;
class OptionsMenu;
class CreditScreen;
class LevelSelectMenu;

enum State {
	Menu,
	PlayScreen,
	Options,
	Credits,
	LevelSelect,
	Multiplayer
};

using namespace std;

class Game
{
public:
	// Public Functions
	Game();
	~Game();
	void run();
	void setGameState(State state);
	void fadeToState(State state);
	void fade();
private:
	void processEvents();
	void update(const float & dt);
	void render();
	void initialiseEntities();
	void initialiseSystems();
	void initialiseFactories();
	void setUpFont();
	void quit();
	int test_haptic(SDL_Joystick * joystick);

	// SDL Window
	SDL_Window * p_window;
	SDL_Renderer * m_renderer;
	int m_windowWidth = 1920;
	int m_windowHeight = 1080;
	bool m_quit = false;
	TTF_Font* Sans;

	// ECS Entities
	std::vector<Entity*> m_entityList;
	Entity * m_player;

	// ECS Components
	BodyComponent * m_playerBody;

	// Factories
	PlayerFactory * m_playerFactory;

	// Misc
	Camera m_camera;

	// ECS Systems
	RenderSystem m_renderSystem;
	PhysicsSystem m_physicsSystem;
	ControlSystem m_controlSystem;
	AnimationSystem m_animationSystem;

	// Input
	InputHandler * inputHandler;
	const int JOYSTICK_DEAD_ZONE = 16000;
	SDL_Joystick* gGameController = NULL;
	SDL_Haptic* gControllerHaptic = NULL;

	// Resources
	ResourceManager * m_resourceManager;

	// Test - TO BE REMOVED
	SDL_Texture * texture;
	SDL_Texture * square;
	Mix_Music *	m_testMusic;
  
	// Box2D
	b2Vec2 m_gravity;
	b2World m_world;

	// Level
	Level * level;

	// Scene Transitions
	SDL_Rect m_transitionScreen;
	float m_transitionAlphaPercent;
	State m_gameState;
	State m_nextState;
	bool fadeOn;
	bool fadeOff;
	bool doneFading;

	// UI/UX
	std::vector<Button *> m_buttons;
	MainMenu * m_menu;
	OptionsMenu * m_options;
	CreditScreen * m_credits;
	LevelSelectMenu * m_levelSelect;

	// Networking
	NetworkingSystem m_network;
};
#endif // !GAME_H
