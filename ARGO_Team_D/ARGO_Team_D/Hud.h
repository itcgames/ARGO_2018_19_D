#ifndef HUD_H
#define HUD_H

#include<SDL.h>
#include<SDL_image.h>
#include"Camera.h"
#include<SDL_ttf.h>
#include<iostream>
#include<string>
#include"ECS/Components/HealthComponent.h"
#include"ECS/Entities/Entity.h"
#include"Observers/LevelData.h"

struct HudComponents {
	HealthComponent * health;
};

class Hud
{
public:
	Hud(Camera & cam, SDL_Renderer & rend, SDL_Window * window, Entity & player, LevelData * data);
	~Hud();
	void update();
	void draw();
	 
private:
	SDL_Renderer * rend;
	TTF_Font* arial;
	SDL_Color color;
	SDL_Surface* surfaceMessage;
	SDL_Texture* message;
	SDL_Rect message_rect;


	SDL_Surface* surfaceMessage2;
	SDL_Texture* message2;
	SDL_Rect message_rect2;

	SDL_Surface* surfaceMessage3;
	SDL_Texture* message3;
	SDL_Rect message_rect3;


	std::string string = "";
	std::string string2 = "";
	std::string string3 = "";
	int windowWidth;
	int windowHeight;


	Camera & m_cam;
	Entity * m_player;
	std::vector<std::string> allowedTypes;

	SDL_Surface * image;
	SDL_Texture * texture;
	SDL_Rect srcrect;
	SDL_Rect dstrect;
	SDL_Rect dstrect2;
	SDL_Rect dstrect3;

	int lives;
	int health;

	LevelData * m_lvlData;
};

#endif // !HUD_H
