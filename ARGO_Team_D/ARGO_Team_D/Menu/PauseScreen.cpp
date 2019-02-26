#include "PauseScreen.h"

PauseScreen::PauseScreen(float width, float height, Game & game, SDL_Renderer * renderer, SDL_Window * window, Camera & camera): Screen()
{
	m_game = &game;
	this->window = window;
	rend = renderer;
	m_width = width;
	m_height = height;
	m_cam = &camera;

	Label * lbl = new Label("Pause", m_cam->m_position.x - m_cam->getBounds().x / m_cam->m_scale.x, 
		m_cam->m_position.y - m_cam->getBounds().y / m_cam->m_scale.y, 
		500, 300, SDL_Color{ 200, 0, 0, 255 }, 
		rend, this->window);

	Button * btn = new Button("Continue", m_cam->m_position.x - m_cam->getBounds().x / m_cam->m_scale.x,
		m_cam->m_position.y - m_cam->getBounds().y / m_cam->m_scale.y,
		300, 100, SDL_Color{ 200, 0, 0, 255 },
		rend, this->window);

	Button * btn2 = new Button("Main Menu", m_cam->m_position.x - m_cam->getBounds().x / m_cam->m_scale.x,
		m_cam->m_position.y - m_cam->getBounds().y / m_cam->m_scale.y,
		300, 100, SDL_Color{ 200, 0, 0, 255 },
		rend, this->window);

	lbl->doTransitions(false);
	btn->doTransitions(false);
	btn2->doTransitions(false);


	btn->Enter = std::bind(&PauseScreen::GoToGame, this);
	btn2->Enter = std::bind(&PauseScreen::GoToMenu, this);


	m_buttons.push_back(btn);
	m_buttons.push_back(btn2);
	m_labels.push_back(lbl);

	m_transitionScreen.x = 0;
	m_transitionScreen.y = 0;
	m_transitionScreen.w = m_width;
	m_transitionScreen.h = m_height;

	m_transitionAlphaPercent = 100;


}

PauseScreen::~PauseScreen()
{
}

void PauseScreen::GoToMenu()
{
	//m_game->setGameState(State::Menu);
	m_game->fadeToState(State::Menu);
	for (auto & b : m_buttons)
	{
		b->reset();
	}
	for (auto & l : m_labels)
	{
		l->reset();
	}
}

void PauseScreen::GoToGame()
{
	for (auto & b : m_buttons)
	{
		b->reset();
	}
	for (auto & l : m_labels)
	{
		l->reset();
	}
	m_game->fadeToState(State::PlayScreen);
}

void PauseScreen::updatePositions()
{
	for (auto l : m_labels)
	{
		l->setPosition(m_cam->m_position.x - m_cam->getBounds().x - 250 / m_cam->m_scale.x, m_cam->m_position.y - m_cam->getBounds().y - 500 / m_cam->m_scale.y);
	}
	
	m_buttons.at(0)->setPosition(m_cam->m_position.x - m_cam->getBounds().x - 150 / m_cam->m_scale.x, m_cam->m_position.y - m_cam->getBounds().y - 150 / m_cam->m_scale.y);
	m_buttons.at(1)->setPosition(m_cam->m_position.x - m_cam->getBounds().x - 150 / m_cam->m_scale.x, m_cam->m_position.y - m_cam->getBounds().y  / m_cam->m_scale.y);
}

void PauseScreen::drawBackground()
{
	SDL_SetRenderDrawColor(rend, 0, 0, 0, 125);
	SDL_RenderFillRect(rend, &m_transitionScreen);
}
