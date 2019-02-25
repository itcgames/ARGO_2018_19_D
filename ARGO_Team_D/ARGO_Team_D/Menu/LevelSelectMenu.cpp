#include "LevelSelectMenu.h"

LevelSelectMenu::LevelSelectMenu(float width, float height, Game & game, SDL_Renderer * renderer, SDL_Window * window)
{
	m_game = &game;
	this->window = window;
	rend = renderer;
	m_width = width;
	m_height = height;


	m_labels.push_back(new Label("Level Select", m_width / 2.80, 0, 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Level 1", m_width / 2.5, 130, 150, 50, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.at(0)->Enter = std::bind(&LevelSelectMenu::LoadLevel1, this);
	m_buttons.push_back(new Button("Level 2", m_width / 2.5, 210, 150, 50, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.at(1)->Enter = std::bind(&LevelSelectMenu::LoadLevel2, this);
	m_buttons.push_back(new Button("Level 3", m_width / 2.5, 290, 150, 50, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Go Back", m_width / 2.5, 370, 150, 50, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.at(3)->Enter = std::bind(&LevelSelectMenu::GoToMenu, this); //func bind
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
