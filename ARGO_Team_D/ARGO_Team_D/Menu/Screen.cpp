#include"Screen.h"

Screen::Screen() 
{}

void Screen::handleInput(SDL_Event theEvent) 
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
			if (b->m_visible) {
				b->mousePress();

				if (b->isClicked)
				{
					for (auto & c : m_buttons)
					{
						c->goToTransition();
					}
					for (auto & l : m_labels)
					{
						l->goToTransition();
					}

				}
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
				if (b->m_visible) {
					b->mousePress();

					if (b->isClicked)
					{
						for (auto & c : m_buttons)
						{
							c->goToTransition();
						}
						for (auto & l : m_labels)
						{
							l->goToTransition();
						}
					}
				}
			}
			break;
		}
	}
}

void Screen::update() 
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
		int timesHit = 0;
		while (!m_buttons.at(m_selectedItem)->m_visible) {
			if (m_selectedItem != m_buttons.size() - 1) {
				if (!m_buttons.at(m_selectedItem)->m_visible) {
					m_selectedItem++;
				}
			}
			else {
				m_selectedItem = 0;
			}
			timesHit++;
			if (timesHit >= m_buttons.size()) {
				m_selectedItem = 0;
				break;
			}
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
		if (b->m_visible)
			b->update();
	}
	for (auto & l : m_labels) 
	{
		l->update();
	}
}


void Screen::draw() 
{
	for (auto & b : m_buttons)
	{
		if (b->m_visible)
			b->draw();
	}
	for (auto & l : m_labels)
	{
		l->draw();
	}
}

bool Screen::itemSelected()
{
	return false;
}