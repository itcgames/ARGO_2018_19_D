#ifndef MAINMENU_H
#define MAINMENU_H
#include"Screen.h"
#include"../Game.h"

class Game;

class MainMenu: public Screen
{
public:
	MainMenu(float width, float height, Game& game, SDL_Renderer * renderer, SDL_Window * window);
	~MainMenu();
	void GoToPlay(); //go to playing state
	void GoToOptions();
	void GoToCredits();
	void GoToLevelSelect();
private:
	Game * m_game;
};

#endif // !MAINMENU_H