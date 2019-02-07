#include "CreditsScreen.h"

CreditScreen::CreditScreen(float width, float height, Game & game, SDL_Renderer * renderer, SDL_Window * window)
{
	m_game = &game;
	this->window = window;
	rend = renderer;
	m_width = width;
	m_height = height;


	label = new Label("Credits", m_width / 2.70, 0, 200, 100, SDL_Color{ 0, 0, 255, 255 }, rend, this->window);
	label2 = new Label("Made by Michael", m_width / 2.90, 200, 300, 100, SDL_Color{ 0, 0, 255, 255 }, rend, this->window);
	m_buttons.push_back(new Button("Go Back", m_width / 2.5, 370, 150, 50, SDL_Color{ 0, 0, 255, 255 }, rend, this->window));
	m_buttons.at(0)->Enter = std::bind(&CreditScreen::GoToMenu, this); //func bind
}

CreditScreen::~CreditScreen()
{
}

void CreditScreen::handleMouse(SDL_Event theEvent)
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
				label2->goToTransition();
			}
		}
		break;
	}
}

void CreditScreen::draw()
{
	for (auto & b : m_buttons)
	{
		b->draw();
	}
	label->draw();
	label2->draw();
}

void CreditScreen::update()
{
	for (auto & b : m_buttons)
	{
		b->update();
	}
	label->update();
	label2->update();
}

bool CreditScreen::itemSelected()
{
	return false;
}

void CreditScreen::GoToMenu()
{
	m_game->setGameState(State::Menu);
	for (auto & b : m_buttons)
	{
		b->reset();
	}
	label->reset();
	label2->reset();
}
