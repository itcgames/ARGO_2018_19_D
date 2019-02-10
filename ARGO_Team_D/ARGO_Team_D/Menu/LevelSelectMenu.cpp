#include "LevelSelectMenu.h"

LevelSelectMenu::LevelSelectMenu(float width, float height, Game & game, SDL_Renderer * renderer, SDL_Window * window)
{
	m_game = &game;
	this->window = window;
	rend = renderer;
	m_width = width;
	m_height = height;


	label = new Label("Level Select", m_width / 2.70, 0, 250, 100, SDL_Color{ 0, 0, 255, 255 }, rend, this->window);
	m_buttons.push_back(new Button("Level 1", m_width / 2.5, 130, 150, 50, SDL_Color{ 0, 0, 255, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Level 2", m_width / 2.5, 210, 150, 50, SDL_Color{ 0, 0, 255, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Level 3", m_width / 2.5, 290, 150, 50, SDL_Color{ 0, 0, 255, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Go Back", m_width / 2.5, 370, 150, 50, SDL_Color{ 0, 0, 255, 255 }, rend, this->window));
	m_buttons.at(3)->Enter = std::bind(&LevelSelectMenu::GoToMenu, this); //func bind
}

LevelSelectMenu::~LevelSelectMenu()
{
}

void LevelSelectMenu::handleMouse(SDL_Event theEvent)
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
				}
			}
			break;
		}
	}
}

void LevelSelectMenu::draw()
{
	for (auto & b : m_buttons)
	{
		b->draw();
	}
	label->draw();
}

void LevelSelectMenu::update()
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
}

bool LevelSelectMenu::itemSelected()
{
	return false;
}

void LevelSelectMenu::GoToMenu()
{
	m_game->setGameState(State::Menu);
	for (auto & b : m_buttons)
	{
		b->reset();
	}
	label->reset();
}
