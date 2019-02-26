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
	m_buttons.push_back(new Button("Back", m_width / 2.35, 650, 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.at(0)->Enter = std::bind(&LobbyScreen::StartGame, this);
	m_buttons.at(1)->Enter = std::bind(&LobbyScreen::GoToMenu, this);

}

LobbyScreen::~LobbyScreen()
{
}

void LobbyScreen::StartGame()
{
	m_game->loadAlevel(0);
	m_game->fadeToState(State::PlayScreen);
	m_game->m_network.joinServer();
	for (auto & b : m_buttons)
	{
		b->reset();
	}
	for (auto & l : m_labels)
	{
		l->reset();
	}
}

void LobbyScreen::GoToMenu()
{
	m_game->setGameState(State::Menu);
	for (auto & b : m_buttons)
	{
		b->reset();
	}
	for (auto & l : m_labels)
	{
		l->reset();
	}
}
