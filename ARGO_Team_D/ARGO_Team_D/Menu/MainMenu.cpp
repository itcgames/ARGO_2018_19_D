#include "MainMenu.h"

MainMenu::MainMenu(float width, float height, Game & game, SDL_Renderer * renderer, SDL_Window * window)
{
	m_game = &game;
	this->window = window;
	rend = renderer;
	m_width = width;
	m_height = height;


	label = new Label("ARGO", m_width / 2.70, 0, 200, 100, SDL_Color{ 0, 0, 255, 255 }, rend, this->window);
	m_buttons.push_back(new Button("Play", m_width / 2.5, 130, 100, 50, SDL_Color{ 0, 0, 255, 255 }, rend, this->window));
	m_buttons.at(0)->Enter = std::bind(&MainMenu::GoToPlay, this);
	m_buttons.push_back(new Button("Options", m_width / 2.5, 210, 150, 50, SDL_Color{ 0, 0, 255, 255 }, rend, this->window));
	m_buttons.at(1)->Enter = std::bind(&MainMenu::GoToOptions, this);
	m_buttons.push_back(new Button("Level Select", m_width / 2.5, 290, 200, 50, SDL_Color{ 0, 0, 255, 255 }, rend, this->window));
	m_buttons.at(2)->Enter = std::bind(&MainMenu::GoToLevelSelect, this);
	m_buttons.push_back(new Button("Credits", m_width / 2.5, 370, 150, 50, SDL_Color{ 0, 0, 255, 255 }, rend, this->window));
	m_buttons.at(3)->Enter = std::bind(&MainMenu::GoToCredits, this);
}

MainMenu::~MainMenu()
{
}

void MainMenu::handleMouse(SDL_Event theEvent)
{
	switch (theEvent.type) {
	case SDL_MOUSEMOTION:
		if (SDL_NumJoysticks() == 0)
		{
			int x, y;

			SDL_GetMouseState(&x, &y);

			for (auto & b : m_buttons)
			{
				b->getMouseCollision(x, y);
			}
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

void MainMenu::draw()
{
	for (auto & b : m_buttons)
	{
		b->draw();
	}
	label->draw();
}

void MainMenu::update()
{
	for (auto & b : m_buttons)
	{
		b->update();
	}

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
	label->update();
}

bool MainMenu::itemSelected()
{
	return false;
}

void MainMenu::GoToPlay()
{
	m_game->fadeToState(State::PlayScreen);
	for (auto & b : m_buttons)
	{
		b->reset();
	}
	label->reset();
}

void MainMenu::GoToOptions()
{
	for (auto & b : m_buttons)
	{
		b->reset();
	}
	label->reset();
	m_game->setGameState(State::Options);
	
}

void MainMenu::GoToCredits()
{
	m_game->setGameState(State::Credits);
	for (auto & b : m_buttons)
	{
		b->reset();
	}
	label->reset();
}

void MainMenu::GoToLevelSelect()
{
	m_game->setGameState(State::LevelSelect);
	for (auto & b : m_buttons)
	{
		b->reset();
	}
	label->reset();
}
