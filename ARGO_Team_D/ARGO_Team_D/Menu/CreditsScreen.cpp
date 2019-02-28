#include "CreditsScreen.h"

CreditScreen::CreditScreen(float width, float height, Game & game, SDL_Renderer * renderer, SDL_Window * window): Screen()
{
	m_game = &game;
	this->window = window;
	rend = renderer;
	m_width = width;
	m_height = height;


	m_labels.push_back(new Label("Credits", m_width / 3.50, 50, 800, 200, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_labels.push_back(new Label("Developed by Michael Bridgette, Liam Hickey, Eric O'Toole and Dylan Murphy", m_width / 25, 300, 1800, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_labels.push_back(new Label("Art provided by Billie Jean Doheny and Angela Young", m_width / 6, 500, 1300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Back",m_width / 2.35, 800, 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
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
