#ifndef MAINMENU_H
#define MAINMENU_H
#include"../Game.h"
#include"Button.h"
#include<SDL.h>

class Game;

class MainMenu
{
public:
	MainMenu(float width, float height, Game& game, SDL_Renderer * renderer, SDL_Window * window);
	~MainMenu();
	void handleMouse(SDL_Event theEvent);
	void draw(); //draw
	void update();//update
	bool itemSelected(); //item selected
	void GoToPlay(); //go to playing state
private:
	Game * m_game;
	SDL_Renderer * rend;
	SDL_Window * window;
	std::vector<Button *> m_buttons;
	float m_width;
	float m_height;
};

#endif // !MAINMENU_H

