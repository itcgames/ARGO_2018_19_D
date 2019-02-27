#ifndef OPTIONS_H
#define OPTIONS_H
#include"../Game.h"
#include"Screen.h"
#include<SDL.h>
class Game;
class OptionsMenu: public Screen 
{
public:
	OptionsMenu(float width, float height, Game& game, SDL_Renderer * renderer, SDL_Window * window, bool &vib);
	~OptionsMenu();
	void GoToMenu(); //go to playing state
private:
	Game * m_game;
	bool * vibration;
};
#endif // !OPTIONS_H
