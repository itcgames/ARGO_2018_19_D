#ifndef OPTIONS_H
#define OPTIONS_H
#include"../Game.h"
#include"Button.h"
#include"Label.h"
#include<SDL.h>
class Game;
class OptionsMenu {
public:
	OptionsMenu(float width, float height, Game& game, SDL_Renderer * renderer, SDL_Window * window);
	~OptionsMenu();
	void handleMouse(SDL_Event theEvent);
	void draw(); //draw
	void update();//update
	bool itemSelected(); //item selected
	void GoToMenu(); //go to playing state
private:
	Game * m_game;
	SDL_Renderer * rend;
	SDL_Window * window;
	std::vector<Button *> m_buttons;
	Label * label;
	float m_width;
	float m_height;
};
#endif // !OPTIONS_H
