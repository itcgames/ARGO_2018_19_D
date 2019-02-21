#ifndef HUD_H
#define HUD_H

#include<SDL.h>
#include<SDL_image.h>
#include"Camera.h"
#include<SDL_ttf.h>
#include<iostream>
#include<string>

class Hud
{
public:
	Hud(Camera & cam, SDL_Renderer & rend, SDL_Window * window);
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

	std::string string = "";
	int windowWidth;
	int windowHeight;


	Camera & m_cam;


	SDL_Surface * image;
	SDL_Texture * texture;
	SDL_Rect srcrect;
	SDL_Rect dstrect;
	SDL_Rect dstrect2;
	SDL_Rect dstrect3;
};

#endif // !HUD_H
