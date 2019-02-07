#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "ECS/Entities/Entity.h"
#include "ECS/Systems/RenderSystem.h"
#include <tmxlite/Map.hpp>
#include "InputHandler.h"
#include "Resource Manager/ResourceManager.h"
#include "ControlSystem.h"
#include <Box2D\Box2D.h>
#include "Level/Level.h"


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

	InputHandler *inputHandler;

	ResourceManager* m_resourceManager;

	SDL_Texture * texture;
	SDL_Texture * square;
	Mix_Music *	m_testMusic;

	ControlSystem m_controlSystem;
  
	b2Vec2 m_gravity;
	b2World m_world;

	// Box2D Test Code
	float b1X = 400.f;
	float b1Y = 450.f;
	float b2X = 400.f;
	float b2Y = 0.f;

	b2BodyDef m_bodyDef1;
	b2Body * m_body1;
	b2PolygonShape m_poly1;
	b2FixtureDef m_fixture1;

	b2BodyDef m_bodyDef2;
	b2Body * m_body2;
	b2PolygonShape m_poly2;
	b2FixtureDef m_fixture2;
	Level * level;
};
#endif // !GAME_H
