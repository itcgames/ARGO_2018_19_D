#include "LobbyScreen.h"

LobbyScreen::LobbyScreen(float width, float height, Game& game, SDL_Renderer * renderer, SDL_Window * window): Screen()
{
	m_game = &game;
	this->window = window;
	rend = renderer;
	m_width = width;
	m_height = height;


	m_labels.push_back(new Label("Lobby", m_width / 3.50, -50, 800, 400, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Start Game", m_width / 2.35, 500, 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));

}

LobbyScreen::~LobbyScreen()
{
}

void LobbyScreen::StartGame()
{

}
