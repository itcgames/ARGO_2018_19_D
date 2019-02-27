#include "CreditsScreen.h"

CreditScreen::CreditScreen(float width, float height, Game & game, SDL_Renderer * renderer, SDL_Window * window): Screen()
{
	m_game = &game;
	this->window = window;
	rend = renderer;
	m_width = width;
	m_height = height;


	m_labels.push_back(new Label("Credits", m_width / 2.50, 0, 300, 200, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_labels.push_back(new Label("Dylan : Programming ", m_width / 3.0, 200, 600, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_labels.push_back(new Label("Eric : Programming", m_width / 3.0, 300, 600, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_labels.push_back(new Label("Michael : Programming", m_width / 3.0, 400, 600, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_labels.push_back(new Label("Liam : Programming", m_width / 3.0, 500, 600, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_labels.push_back(new Label("Billie Jean : Art", m_width / 3.0, 600, 400, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_labels.push_back(new Label("Angie : Art", m_width / 3.0, 700, 400, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Go Back", m_width / 2.5, 825, 300, 150, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
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
