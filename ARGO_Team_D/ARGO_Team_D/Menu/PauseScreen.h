#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include "Screen.h"
#include "../Game.h"
#include "../Camera.h"
class PauseScreen: public Screen {
public:
	PauseScreen(float width, float height, Game& game, SDL_Renderer * renderer, SDL_Window * window, Camera & camera);
	~PauseScreen();
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

#endif // !PAUSESCREEN_H

