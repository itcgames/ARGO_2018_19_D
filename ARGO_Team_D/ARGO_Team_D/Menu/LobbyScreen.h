#ifndef LOBBYSCREEN_H
#define LOBBYSCREEN_H
#include "Screen.h"
#include "../Game.h"
class LobbyScreen: public Screen
{
public:
	LobbyScreen(float width, float height, Game& game, SDL_Renderer * renderer, SDL_Window * window);
	~LobbyScreen();
	void StartGame();
private:
	Game * m_game;
};

#endif // !LOBBYSCREEN_H

