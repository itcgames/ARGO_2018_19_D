#include "MainMenu.h"

MainMenu::MainMenu(float width, float height, Game & game, SDL_Renderer * renderer, SDL_Window * window)
{
	m_game = &game;
	this->window = window;
	rend = renderer;
	m_width = width;
	m_height = height;

	m_buttons.push_back(new Button("Play", m_width / 2.5, 50, 100, 50, SDL_Color{ 0, 0, 255, 255 }, rend, this->window));
	m_buttons.at(0)->Enter = std::bind(&MainMenu::GoToPlay, this);
	m_buttons.push_back(new Button("Options", m_width / 2.5, 130, 150, 50, SDL_Color{ 0, 0, 255, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Level Select", m_width / 2.5, 210, 200, 50, SDL_Color{ 0, 0, 255, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Credits", m_width / 2.5, 290, 150, 50, SDL_Color{ 0, 0, 255, 255 }, rend, this->window));
}

MainMenu::~MainMenu()
{
}

void MainMenu::handleMouse(SDL_Event theEvent)
{
	switch (theEvent.type) {
	case SDL_MOUSEMOTION:
		int x, y;

		SDL_GetMouseState(&x, &y);

		for (auto & b : m_buttons)
		{
			b->getMouseCollision(x, y);
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		for (auto & b : m_buttons)
		{
			b->mousePress();

			if (b->isClicked)
			{
				for (auto & c : m_buttons)
				{
					c->goToTransition();
				}
			}
		}
		break;
	}
}

void MainMenu::draw()
{
	for (auto & b : m_buttons)
	{
		b->draw();
	}
}

void MainMenu::update()
{
	for (auto & b : m_buttons)
	{
		b->update();
	}
}

bool MainMenu::itemSelected()
{
	return false;
}

void MainMenu::GoToPlay()
{
	m_game->setGameState(State::PlayScreen);
}
