#ifndef LEVELSELECTMENU_H
#define LEVELSELECTMENU_H

#include<SDL.h>
#include"Button.h"
#include"Label.h"
#include<vector>
#include"../Game.h"

class Game;

class LevelSelectMenu {
public:
	LevelSelectMenu(float width, float height, Game& game, SDL_Renderer * renderer, SDL_Window * window);
	~LevelSelectMenu();
	void handleMouse(SDL_Event theEvent);
	void draw(); //draw
	void update();//update
	bool itemSelected(); //item selected
	void GoToMenu();
private:
	Game * m_game;
	SDL_Renderer * rend;
	SDL_Window * window;
	std::vector<Button *> m_buttons;
	Label * label;
	Label * label2;
	float m_width;
	float m_height;

	int m_selectedItem = 0;
	const int JOYSTICK_DEAD_ZONE = 16000;
	bool activateJoystick = false;


};

#endif // !LEVELSELECTMENU_H

