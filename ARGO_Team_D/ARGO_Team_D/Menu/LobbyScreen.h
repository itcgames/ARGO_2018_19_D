#ifndef LOBBYSCREEN_H
#define LOBBYSCREEN_H
#include "Screen.h"
#include "../Game.h"
#include "../ECS/Systems/NetworkingSystem.h"

class Game;

class LobbyScreen: public Screen
{
public:
	LobbyScreen(float width, float height, Game& game, SDL_Renderer * renderer, SDL_Window * window);
	~LobbyScreen();
	void StartGame();
	void GoToMenu();
	void setLobbyInformation(std::vector<NetworkingSystem::Lobby> & lobbies);
	void createLobby();
	void joinLobby();
	void leaveLobby();
	void startLobby();
	void updateLobbies();
	void draw() override;
private:
	Game * m_game;
	SDL_Rect m_lobbyRect;
	int lobbyIn = 0;

};

#endif // !LOBBYSCREEN_H

