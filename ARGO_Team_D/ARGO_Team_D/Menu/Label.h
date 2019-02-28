#ifndef LABEL_H
#define LABEL_H

#include<SDL.h>
#include<SDL_ttf.h>
#include<functional>
#include<iostream>

class Label {

public:
	Label(const char * string, int x, int y, int w, int h, SDL_Color color, SDL_Renderer * renderer, SDL_Window * window);
	~Label();
	void draw();
	void update();
	void transition();
	void goToTransition();
	void reset();
	void Lerp(int startPosX, int startPosY, int destX, int destY);

	void setPosition(int x, int y);
	void doTransitions(bool b);
	void isACheckBoxLabel(bool * b);
	void setSize(int x, int y);
	void setString(std::string s);
	int displayX;
	int displayY;
	int displayWidth;
	int displayHeight;
private:

	bool * condition;
	SDL_Renderer * rend;
	TTF_Font* arial;
	SDL_Color color;
	SDL_Surface* surfaceMessage;
	SDL_Texture* message;
	SDL_Rect message_rect;

	bool isTransitioning = false;
	int transitionCount = 0;
	const char * string = "";
	int windowWidth;
	int windowHeight;
	float percent = 0;
	int startPosX;
	int startPosY;
	bool onScreen;
	bool doTransition;

	bool isCheckBoxLabel;
};

#endif // !LABEL_H

