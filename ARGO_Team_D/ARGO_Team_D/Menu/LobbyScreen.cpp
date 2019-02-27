#include "LobbyScreen.h"

LobbyScreen::LobbyScreen(float width, float height, Game& game, SDL_Renderer * renderer, SDL_Window * window): Screen()
{
	m_game = &game;
	this->window = window;
	rend = renderer;
	m_width = width;
	m_height = height;


	m_labels.push_back(new Label("Lobby", m_width / 3.50, -50, 800, 400, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_labels.at(0)->doTransitions(false);
	//m_buttons.push_back(new Button("Start Game", m_width / 3, m_height - ((m_height / 10) * 2), 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Back", m_width / 9, m_height - ((m_height / 10) * 2), 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Create Lobby", m_width / 3.35, m_height - ((m_height / 10) * 2), 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Join lobby", m_width / 1.65, m_height - ((m_height / 10) * 2), 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Start", -1000, m_height - ((m_height / 10) * 2), 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.at(0)->Enter = std::bind(&LobbyScreen::GoToMenu, this);
	m_buttons.at(1)->Enter = std::bind(&LobbyScreen::createLobby, this);
	m_buttons.at(2)->Enter = std::bind(&LobbyScreen::joinLobby, this);
	m_buttons.at(0)->doTransitions(false);
	m_buttons.at(1)->doTransitions(false);
	m_buttons.at(2)->doTransitions(false);
}

LobbyScreen::~LobbyScreen()
{
}

void LobbyScreen::StartGame()
{
	m_game->loadAlevel(0);
	m_game->fadeToState(State::PlayScreen);
	for (auto & b : m_buttons)
	{
		b->reset();
	}
	for (auto & l : m_labels)
	{
		l->reset();
	}
}

void LobbyScreen::GoToMenu()
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

void LobbyScreen::setLobbyInformation(std::vector<NetworkingSystem::Lobby>& lobbies)
{
	int lobbyHeight = (m_height / 3.f);
	int xPos = m_width / 5;
	int labelHeight = 100;
	int labelSpacing = 20;
	if (lobbies.size() > m_labels.size() - 1) {
		for (int i = m_labels.size() - 1; i < lobbies.size(); ++i) {
			auto & lobbyInfo = lobbies[i];
			m_labels.push_back(new Label((lobbyInfo.m_name.c_str() + std::string(": ") + std::to_string(lobbyInfo.m_numPlayers)).c_str(), xPos, lobbyHeight + ((labelHeight + labelSpacing) * (i)), m_width / 5, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
			m_labels.back()->doTransitions(false);
		}
	}
}

void LobbyScreen::createLobby()
{
	if (m_game->m_network.createNewLobby()) {

	}
	setLobbyInformation(m_game->m_network.getLobbies());
}

void LobbyScreen::joinLobby()
{
}
