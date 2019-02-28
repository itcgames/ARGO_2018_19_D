#pragma once
#include<SDL.h>
#include<SDL_ttf.h>
#include<functional>
#include<string>
class Button {
public:
	Button(const char * string,int x, int y, int w, int h, SDL_Color color, SDL_Renderer * renderer, SDL_Window * window);
	~Button();

	void update();
	void draw();
	void mousePress();
	void transition();
	void goToTransition();
	void reset();
	bool isClicked = false;

	void getMouseCollision(int x, int y);
	typedef std::function<void()> Callback;
	Callback Enter;

	void Lerp(int startPosX, int startPosY, int destX, int destY);
	void Focus(bool b);

	void setPosition(int x, int y);
	void doTransitions(bool b);
	

	void makeCheckbox(bool * b);
	bool m_visible = true;
private:

	bool * condition;

	SDL_Renderer * rend;
	TTF_Font* arial;
	SDL_Color color;
	SDL_Surface* surfaceMessage;
	SDL_Texture* message;
	SDL_Rect message_rect;

	SDL_Rect r;

	SDL_Color nonFocusColor;
	SDL_Color focusColor;
	std::string string = "";
	std::string checkboxString;
	bool hasFocus = false;
	float alpha;
	bool isTransitioning = false;
	int transitionCount = 0;

	int windowWidth;
	int windowHeight;

	float percent=0;

	int startPosX;
	int startPosY;

	int displayX;
	int displayY;

	bool onScreen;

	int displayWidth;
	int displayHeight;

	bool activateFunction;

	bool doTransition;

	bool isACheckbox;
};