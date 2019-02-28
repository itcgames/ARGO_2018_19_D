#ifndef OPTIONS_H
#define OPTIONS_H
#include"../Game.h"
#include"Screen.h"
#include<SDL.h>
class Game;
class OptionsMenu: public Screen 
{
public:
	OptionsMenu(float width, float height, Game& game, SDL_Renderer * renderer, SDL_Window * window, bool &vib, bool &mus);
	~OptionsMenu();
	void GoToMenu();
private:
	Game * m_game;
	bool * vibration;
	bool * music;
};
#endif // !OPTIONS_H
