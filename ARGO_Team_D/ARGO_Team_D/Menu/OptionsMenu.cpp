#include "OptionsMenu.h"

OptionsMenu::OptionsMenu(float width, float height, Game & game, SDL_Renderer * renderer, SDL_Window * window, bool &vib, bool &mus)
{
	m_game = &game;
	this->window = window;
	rend = renderer;
	m_width = width;
	m_height = height;

	vibration = &vib;
	music = &mus;
	
	m_labels.push_back(new Label("Options", m_width / 3.50, 100, 800, 200, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	auto btn = new Button("Vibration", m_width / 2.35, 350, 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window);
	btn->makeCheckbox(vibration);
	m_buttons.push_back(btn);

	auto lbl = new Label("Options1", m_width / 1.50f, 350, 100, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window);
	lbl->isACheckBoxLabel(vibration);
	m_labels.push_back(lbl);

	auto btn2 = new Button("Music", m_width / 2.35, 500, 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window);
	btn2->makeCheckbox(music);
	m_buttons.push_back(btn2);

	auto lbl2 = new Label("Options1", m_width / 1.50f, 500, 100, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window);
	lbl2->isACheckBoxLabel(music);
	m_labels.push_back(lbl2);

	m_buttons.push_back(new Button("Go Back", m_width / 2.35, 650, 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.at(2)->Enter = std::bind(&OptionsMenu::GoToMenu, this); //func bind

}

OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::GoToMenu()
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
