#include "LevelSelectMenu.h"

LevelSelectMenu::LevelSelectMenu(float width, float height, Game & game, SDL_Renderer * renderer, SDL_Window * window)
{
	m_game = &game;
	this->window = window;
	rend = renderer;
	m_width = width;
	m_height = height;


	m_labels.push_back(new Label("Level Select", m_width / 3.50, 50, 800, 200, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Tutorial", m_width / 2.35, 300, 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.at(0)->Enter = std::bind(&LevelSelectMenu::LoadLevel1, this);
	m_buttons.push_back(new Button("Level 2", m_width / 2.35, 450, 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.at(1)->Enter = std::bind(&LevelSelectMenu::LoadLevel2, this);
	m_buttons.push_back(new Button("Level 3", m_width / 2.35, 600, 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.at(2)->Enter = std::bind(&LevelSelectMenu::LoadLevel3, this);
	m_buttons.push_back(new Button("Level 4", m_width / 2.35, 750, 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.at(3)->Enter = std::bind(&LevelSelectMenu::Loadlevel4, this);
	m_buttons.push_back(new Button("Back", m_width / 2.35, 900, 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.at(4)->Enter = std::bind(&LevelSelectMenu::GoToMenu, this); //func bind
}

LevelSelectMenu::~LevelSelectMenu()
{
}

void LevelSelectMenu::GoToMenu()
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

void LevelSelectMenu::LoadLevel1()
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

void LevelSelectMenu::LoadLevel2()
{
	m_game->loadAlevel(1);
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

void LevelSelectMenu::LoadLevel3()
{
	m_game->loadAlevel(2);
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

void LevelSelectMenu::Loadlevel4()
{
	m_game->loadAlevel(3);
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
