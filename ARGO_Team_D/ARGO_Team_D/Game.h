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
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/SpriteComponent.h"
#include <tmxlite/Map.hpp>
#include "InputHandler.h"
#include "Resource Manager/ResourceManager.h"
#include "ControlSystem.h"
#include <Box2D\Box2D.h>
#include "Level/Level.h"
#include "Factories/Factory.h"
#include "Factories/CharacterFactory.h"
#include "Menu/Button.h"
#include "Menu/MainMenu.h"
#include "Menu/OptionsMenu.h"
#include "Menu/CreditsScreen.h"
#include "Menu/LevelSelectMenu.h"
#include "Utils/VectorAPI.h"
#include "Camera.h"
#include<SDL_haptic.h>

class MainMenu;
class OptionsMenu;
class CreditScreen;
class LevelSelectMenu;

enum State {
	Menu,
	PlayScreen,
	Options,
	Credits,
	LevelSelect
};
using namespace std;

class Game
{
public:
	Game();
	~Game();
	void run();
	void setGameState(State state);
	bool fadeOn;
	bool fadeOff;
	bool doneFading;

	void fadeToState(State state);
	void fade();
	int test_haptic(SDL_Joystick * joystick);
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

	int m_windowWidth = 1280;
	int m_windowHeight = 720;
	TTF_Font* Sans;

	RenderSystem m_renderSystem;

	PhysicsSystem m_physicsSystem;

	InputHandler *inputHandler;

	ResourceManager* m_resourceManager;

	SDL_Texture * texture;
	SDL_Texture * square;
	Mix_Music *	m_testMusic;

	ControlSystem m_controlSystem;
  
	b2Vec2 m_gravity;
	b2World m_world;

	Level * level;

	// Box2D Test Code
	float b2X = 500.f;
	float b2Y = 0.f;

	b2BodyDef m_bodyDef2;
	b2Body * m_body2;
	b2PolygonShape m_poly2;
	b2FixtureDef m_fixture2;


	Factory* playerFactory;
	Camera m_camera;
	Entity* player;

	State m_gameState;
	State m_nextState;

	std::vector<Button *> buttons;

	MainMenu * m_menu;
	OptionsMenu * m_options;
	CreditScreen * m_credits;
	LevelSelectMenu * m_levelSelect;

	SDL_Rect m_transitionScreen;
	float m_transitionAlphaPercent;

	std::vector<Entity*> m_entityList;


	//controller stuff
	const int JOYSTICK_DEAD_ZONE = 16000;
	SDL_Joystick* gGameController = NULL;
	SDL_Haptic* gControllerHaptic = NULL;

};
#endif // !GAME_H
