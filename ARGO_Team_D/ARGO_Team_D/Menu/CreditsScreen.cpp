#include "CreditsScreen.h"

CreditScreen::CreditScreen(float width, float height, Game & game, SDL_Renderer * renderer, SDL_Window * window): Screen()
{
	m_game = &game;
	this->window = window;
	rend = renderer;
	m_width = width;
	m_height = height;


	m_labels.push_back(new Label("Credits", m_width / 2.70, 0, 200, 100, SDL_Color{ 0, 0, 255, 255 }, rend, this->window));
	m_labels.push_back(new Label("Made by Michael", m_width / 2.90, 200, 300, 100, SDL_Color{ 0, 0, 255, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Go Back", m_width / 2.5, 370, 150, 50, SDL_Color{ 0, 0, 255, 255 }, rend, this->window));
	m_buttons.at(0)->Enter = std::bind(&CreditScreen::GoToMenu, this); //func bind
}

CreditScreen::~CreditScreen()
{
}


void CreditScreen::GoToMenu()
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
