#include "ModeSelectScreen.h"

ModeSelectScreen::ModeSelectScreen(float width, float height, Game & game, SDL_Renderer * renderer, SDL_Window * window): Screen()
{
	m_game = &game;
	this->window = window;
	rend = renderer;
	m_width = width;
	m_height = height;


	m_labels.push_back(new Label("Mode Select", m_width / 3.50, -50, 800, 400, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Single Player", m_width / 2.35, 350, 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.at(0)->Enter = std::bind(&ModeSelectScreen::GoToGame, this);
	m_buttons.push_back(new Button("Multiplayer", m_width / 2.35, 500, 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.at(1)->Enter = std::bind(&ModeSelectScreen::GoToMultiplayerGame, this);
	m_buttons.push_back(new Button("AI Mode", m_width / 2.35, 650, 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.at(2)->Enter = std::bind(&ModeSelectScreen::GoToAI, this); //func bind
	m_buttons.push_back(new Button("Go Back", m_width / 2.35, 800, 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.at(3)->Enter = std::bind(&ModeSelectScreen::GoToMenu, this); //func bind
}

ModeSelectScreen::~ModeSelectScreen()
{
}

void ModeSelectScreen::GoToGame()
{
	m_game->loadAlevel(0);
	m_game->setAI(false);
	m_game->resetKills();
	m_game->resetPlayerHealth();
	m_game->fadeToState(State::PlayScreen);
	for (auto & b : m_buttons)
	{
		b->reset();
	}
	for (auto & l : m_labels)
	{
		l->reset();
	}
}

void ModeSelectScreen::GoToMultiplayerGame()
{
	m_game->resetPlayerHealth();
	m_game->setAI(false);
	m_game->resetKills();
	m_game->setGameState(State::Lobby);
	m_game->m_network.initClientLocalClient();
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

void ModeSelectScreen::GoToAI()
{
	m_game->loadAlevel(0);
	m_game->setAI(true);
	m_game->resetKills();
	m_game->resetPlayerHealth();
	m_game->fadeToState(State::PlayScreen);
	for (auto & b : m_buttons)
	{
		b->reset();
	}
	for (auto & l : m_labels)
	{
		l->reset();
	}
}

void ModeSelectScreen::GoToMenu()
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
