#ifndef MODESELECTSCREEN_H
#define MODESELECTSCREEN_H
#include "Screen.h"
#include "../Game.h"

class ModeSelectScreen: public Screen
{
public:
	ModeSelectScreen(float width, float height, Game& game, SDL_Renderer * renderer, SDL_Window * window);
	~ModeSelectScreen();
	void GoToGame();
	void GoToMultiplayerGame();
	void GoToAI();
	void GoToMenu();
private:
	Game * m_game;
};

#endif // !MODESELECTSCREEN_H

