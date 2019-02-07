#include "OptionsMenu.h"

OptionsMenu::OptionsMenu(float width, float height, Game & game, SDL_Renderer * renderer, SDL_Window * window)
{
	m_game = &game;
	this->window = window;
	rend = renderer;
	m_width = width;
	m_height = height;


	label = new Label("Options", m_width / 2.70, 0, 200, 100, SDL_Color{ 0, 0, 255, 255 }, rend, this->window);
	m_buttons.push_back(new Button("Options1", m_width / 2.5, 130, 150, 50, SDL_Color{ 0, 0, 255, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Options2", m_width / 2.5, 210, 150, 50, SDL_Color{ 0, 0, 255, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Options3", m_width / 2.5, 290, 150, 50, SDL_Color{ 0, 0, 255, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Go Back", m_width / 2.5, 370, 150, 50, SDL_Color{ 0, 0, 255, 255 }, rend, this->window));
	m_buttons.at(3)->Enter = std::bind(&OptionsMenu::GoToMenu, this); //func bind
}

OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::handleMouse(SDL_Event theEvent)
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
				label->goToTransition();
			}
		}
		break;
	}
}

void OptionsMenu::draw()
{
	for (auto & b : m_buttons)
	{
		b->draw();
	}
	label->draw();
}

void OptionsMenu::update()
{
	for (auto & b : m_buttons)
	{
		b->update();
	}
	label->update();
}

bool OptionsMenu::itemSelected()
{
	return false;
}

void OptionsMenu::GoToMenu()
{
	m_game->setGameState(State::Menu);
	for (auto & b : m_buttons)
	{
		b->reset();
	}
	label->reset();
	
}
