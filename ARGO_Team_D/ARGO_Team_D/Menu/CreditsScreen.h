#ifndef CREDITSCREEN_H
#define CREDITSCREEN_H
#include<SDL.h>
#include"Button.h"
#include"Label.h"
#include<vector>
#include"Screen.h"
#include"../Game.h"

class Game;

class CreditScreen: public Screen {
public:
	CreditScreen(float width, float height, Game& game, SDL_Renderer * renderer, SDL_Window * window);
	~CreditScreen();
	void GoToMenu();
private:
	Game * m_game;
};

#endif // !CREDITSCREEN_H

