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

	case SDL_JOYAXISMOTION:
		if (theEvent.jaxis.which == 0)
		{
			if (theEvent.jaxis.axis == 1)
			{
				//Below of dead zone
				if (theEvent.jaxis.value < -JOYSTICK_DEAD_ZONE)
				{

					if (activateJoystick)
					{
						m_selectedItem--;
						activateJoystick = false;
					}
				}
				//Above of dead zone
				else if (theEvent.jaxis.value > JOYSTICK_DEAD_ZONE)
				{
					if (activateJoystick)
					{
						m_selectedItem++;
						activateJoystick = false;
					}
				}
				else
				{
					//yDir = 0;
					activateJoystick = true;
				}
			}
		}
		break;
	case SDL_JOYBUTTONDOWN:
		//Play rumble at 75% strenght for 500 milliseconds
		//SDL_HapticRumblePlay(gControllerHaptic, 0.75, 500);

		switch (theEvent.jbutton.button)
		{
		case 0:
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
	if (SDL_NumJoysticks() >= 1)
	{
		if (m_selectedItem > (int)m_buttons.size() - 1) //cast to int as .size() returns unsigned int
		{
			m_selectedItem = 0;
		}
		if (m_selectedItem < 0)
		{
			m_selectedItem = m_buttons.size() - 1;
		}

		for (int i = 0; i < m_buttons.size(); i++)
		{
			if (i != m_selectedItem)
			{
				m_buttons.at(i)->Focus(false);
			}
		}
		m_buttons.at(m_selectedItem)->Focus(true);

	}

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
