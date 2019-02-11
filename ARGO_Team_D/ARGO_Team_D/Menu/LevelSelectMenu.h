#ifndef LEVELSELECTMENU_H
#define LEVELSELECTMENU_H

#include<SDL.h>
#include"Screen.h"
#include<vector>
#include"../Game.h"

class Game;

class LevelSelectMenu: public Screen 
{
public:
	LevelSelectMenu(float width, float height, Game& game, SDL_Renderer * renderer, SDL_Window * window);
	~LevelSelectMenu();
	void GoToMenu();
private:
	Game * m_game;
};

#endif // !LEVELSELECTMENU_H

