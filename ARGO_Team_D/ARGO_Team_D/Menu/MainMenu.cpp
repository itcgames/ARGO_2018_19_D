#include "MainMenu.h"

MainMenu::MainMenu(float width, float height, Game & game, SDL_Renderer * renderer, SDL_Window * window): Screen()
{
	m_game = &game;
	this->window = window;
	rend = renderer;
	m_width = width;
	m_height = height;


	m_labels.push_back(new Label("SINDICATE", m_width / 3.50, 100, 800, 200, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Play", m_width / 2.35, 350, 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.at(0)->Enter = std::bind(&MainMenu::GoToPlay, this);
	m_buttons.push_back(new Button("Options", m_width / 2.35, 500, 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.at(1)->Enter = std::bind(&MainMenu::GoToOptions, this);
	m_buttons.push_back(new Button("Level Select", m_width / 2.35, 650, 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.at(2)->Enter = std::bind(&MainMenu::GoToLevelSelect, this);
	m_buttons.push_back(new Button("Credits", m_width / 2.35, 800, 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.at(3)->Enter = std::bind(&MainMenu::GoToCredits, this);
}

MainMenu::~MainMenu()
{
}


void MainMenu::GoToPlay()
{
	//m_game->m_levelManager.loadCurrentLevel(*m_game->m_resourceManager, m_game->m_renderer);
	/*m_game->loadAlevel(0);
	m_game->fadeToState(State::PlayScreen);*/
	m_game->setGameState(State::ModeSelect);
	for (auto & b : m_buttons)
	{
		b->reset();
	}
	for (auto & l : m_labels)
	{
		l->reset();
	}
}

void MainMenu::GoToOptions()
{
	for (auto & b : m_buttons)
	{
		b->reset();
	}
	for (auto & l : m_labels)
	{
		l->reset();
	}
	m_game->setGameState(State::Options);
	
}

void MainMenu::GoToCredits()
{
	m_game->setGameState(State::Credits);
	for (auto & b : m_buttons)
	{
		b->reset();
	}
	for (auto & l : m_labels)
	{
		l->reset();
	}
}

void MainMenu::GoToLevelSelect()
{
	m_game->setGameState(State::LevelSelect);
	for (auto & b : m_buttons)
	{
		b->reset();
	}
	for (auto & l : m_labels)
	{
		l->reset();
	}
}
