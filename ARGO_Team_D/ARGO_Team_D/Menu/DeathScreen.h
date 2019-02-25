#ifndef DEATHSCREEN
#define DEATHSCREEN

#include "Screen.h"
#include "../Game.h"
#include "../Camera.h"

class DeathScreen: public Screen
{
public:
	DeathScreen(float width, float height, Game& game, SDL_Renderer * renderer, SDL_Window * window, Camera & camera);
	~DeathScreen();
	void GoToMenu();
	void GoToGame();
	void updatePositions();
	void drawBackground();
private:
	Game * m_game;
	Camera * m_cam;
	SDL_Rect m_transitionScreen;
	float m_transitionAlphaPercent;
};


#endif // !DEATHSCREEN
