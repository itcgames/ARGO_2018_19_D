#include "DeathScreen.h"

DeathScreen::DeathScreen(float width, float height, Game & game, SDL_Renderer * renderer, SDL_Window * window, Camera & camera): Screen()
{
	m_game = &game;
	this->window = window;
	rend = renderer;
	m_width = width;
	m_height = height;
	m_cam = &camera;

	Label * lbl = new Label("You're Dead!", m_cam->m_position.x - m_cam->getBounds().x / m_cam->m_scale.x,
		m_cam->m_position.y - m_cam->getBounds().y / m_cam->m_scale.y,
		700, 300, SDL_Color{ 0, 0, 0, 255 },
		rend, this->window);

	Button * btn = new Button("Try Again", m_cam->m_position.x - m_cam->getBounds().x / m_cam->m_scale.x,
		m_cam->m_position.y - m_cam->getBounds().y / m_cam->m_scale.y,
		300, 100, SDL_Color{ 0, 0, 0, 255 },
		rend, this->window);

	Button * btn2 = new Button("Main Menu", m_cam->m_position.x - m_cam->getBounds().x / m_cam->m_scale.x,
		m_cam->m_position.y - m_cam->getBounds().y / m_cam->m_scale.y,
		300, 100, SDL_Color{ 0, 0, 0, 255 },
		rend, this->window);

	lbl->doTransitions(false);
	btn->doTransitions(false);
	btn2->doTransitions(false);


	btn->Enter = std::bind(&DeathScreen::GoToGame, this);
	btn2->Enter = std::bind(&DeathScreen::GoToMenu, this);


	m_buttons.push_back(btn);
	m_buttons.push_back(btn2);
	m_labels.push_back(lbl);

	m_transitionScreen.x = 0;
	m_transitionScreen.y = 0;
	m_transitionScreen.w = m_width;
	m_transitionScreen.h = m_height;

	m_transitionAlphaPercent = 100;
}

DeathScreen::~DeathScreen()
{
}

void DeathScreen::GoToMenu()
{
	m_game->m_levelManager.unloadAllLevels();
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

void DeathScreen::GoToGame()
{
	m_game->reloadCurrentlevel();
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

void DeathScreen::updatePositions()
{
	for (auto l : m_labels)
	{
		l->setPosition(m_cam->m_position.x - m_cam->getBounds().x - 325 / m_cam->m_scale.x, m_cam->m_position.y - m_cam->getBounds().y - 500 / m_cam->m_scale.y);
	}

	m_buttons.at(0)->setPosition(m_cam->m_position.x - m_cam->getBounds().x - 150 / m_cam->m_scale.x, m_cam->m_position.y - m_cam->getBounds().y - 150 / m_cam->m_scale.y);
	m_buttons.at(1)->setPosition(m_cam->m_position.x - m_cam->getBounds().x - 150 / m_cam->m_scale.x, m_cam->m_position.y - m_cam->getBounds().y / m_cam->m_scale.y);
}

void DeathScreen::drawBackground()
{
	SDL_SetRenderDrawColor(rend, 255, 0, 0, 125);
	SDL_RenderFillRect(rend, &m_transitionScreen);
}
