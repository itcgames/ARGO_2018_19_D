#include "LobbyScreen.h"

LobbyScreen::LobbyScreen(float width, float height, Game& game, SDL_Renderer * renderer, SDL_Window * window): Screen()
{
	m_game = &game;
	this->window = window;
	rend = renderer;
	m_width = width;
	m_height = height;


	m_labels.push_back(new Label("Lobby", m_width / 3.50, -50, 800, 400, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_labels.push_back(new Label("You Are Here", (m_width / 5) + 350, -500, 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_labels.at(0)->doTransitions(false);
	m_labels.at(1)->doTransitions(false);
	//m_buttons.push_back(new Button("Start Game", m_width / 3, m_height - ((m_height / 10) * 2), 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Back", m_width / 9, m_height - ((m_height / 20) * 2), 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Create Lobby", m_width / 3.35, m_height - ((m_height / 5) * 2), 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Join lobby", m_width / 1.25, m_height - ((m_height / 5) * 2), 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.push_back(new Button("Start", m_width / 2.25, m_height - ((m_height / 10) * 2), 300, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
	m_buttons.at(0)->Enter = std::bind(&LobbyScreen::leaveLobby, this);
	m_buttons.at(1)->Enter = std::bind(&LobbyScreen::createLobby, this);
	m_buttons.at(2)->Enter = std::bind(&LobbyScreen::joinLobby, this);
	m_buttons.at(3)->Enter = std::bind(&LobbyScreen::startLobby, this);
	m_buttons.at(3)->doTransitions(false);
	m_buttons.at(3)->m_visible = false;
	m_buttons.at(0)->doTransitions(false);
	m_buttons.at(1)->doTransitions(false);
	m_buttons.at(2)->doTransitions(false);
	m_buttons.at(3)->doTransitions(false);
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
	m_buttons.at(3)->m_visible = false;
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
	m_buttons.at(3)->m_visible = false;
	for (auto & l : m_labels)
	{
		l->reset();
	}
}

void LobbyScreen::setLobbyInformation(std::vector<NetworkingSystem::Lobby>& lobbies)
{
	int lobbyHeight = (m_height / 3.f);
	int xSpacing = 100;
	int xPos = m_width / 5;
	int labelHeight = 100;
	int labelSpacing = 20;
	int numPreDefLabels = 2;
	if (lobbies.size() > m_labels.size() - numPreDefLabels) {
		for (int i = m_labels.size() - numPreDefLabels; i < lobbies.size(); ++i) {
			auto & lobbyInfo = lobbies[i];
			m_labels.push_back(new Label((lobbyInfo.m_name.c_str() + std::string(": ") + std::to_string(lobbyInfo.m_numPlayers)).c_str(), xPos, lobbyHeight + ((labelHeight + labelSpacing) * (i)), m_width / 5, 100, SDL_Color{ 200, 0, 0, 255 }, rend, this->window));
			m_labels.back()->doTransitions(false);
		}
	}

	int currLobby = m_game->m_network.getMyLobby();
	if (currLobby < 0 || currLobby > lobbies.size() - 1) {
		// Waiting
		currLobby = -1;
	}
	else {
		m_labels.at(1)->setPosition(xSpacing + m_labels.at(currLobby + 2)->displayX + m_labels.at(currLobby + 2)->displayWidth, lobbyHeight + (currLobby * (labelHeight + labelSpacing)));
	}

}

void LobbyScreen::createLobby()
{
	auto & lobbies = m_game->m_network.getLobbies();
	if (m_game->m_network.createNewLobby()) {
		m_buttons.at(3)->m_visible = true;
		m_buttons.at(1)->m_visible = false;
		m_buttons.at(2)->m_visible = false;
	}
	setLobbyInformation(lobbies);
}

void LobbyScreen::joinLobby()
{
	auto & lobbies = m_game->m_network.getLobbies();
	if (m_game->m_network.joinLobby()) {
		m_buttons.at(1)->m_visible = false;
		m_buttons.at(2)->m_visible = false;
	}
	setLobbyInformation(lobbies);
}

void LobbyScreen::leaveLobby()
{
	if (m_game->m_network.leaveLobby()) {
		m_buttons.at(3)->m_visible = false;
		m_buttons.at(1)->m_visible = true;
		m_buttons.at(2)->m_visible = true;
		m_labels.at(1)->setPosition(-1000,-1000);
		auto & lobbies = m_game->m_network.getLobbies();
		setLobbyInformation(lobbies);
	}
	else {
		GoToMenu();
	}
}

void LobbyScreen::startLobby()
{
	std::cout << "Starting" << std::endl;
	m_game->m_network.startLobby();
	m_game->loadAlevel(0);
	m_game->fadeToState(State::PlayScreen);
	for (auto & b : m_buttons)
	{
		b->reset();
	}
	m_buttons.at(3)->m_visible = false;
	for (auto & l : m_labels)
	{
		l->reset();
	}
}

void LobbyScreen::updateLobbies()
{
	auto & lobbies = m_game->m_network.getLobbies();
	int numPreDefLabels = 2;
	setLobbyInformation(lobbies);
	for (int i = numPreDefLabels; i < m_labels.size(); ++i) {
		m_labels.at(i)->setString(lobbies.at(i - numPreDefLabels).m_name.c_str() + std::string(": ") + std::to_string(lobbies.at(i - numPreDefLabels).m_numPlayers));
	}
	m_game->m_network.m_lobbiesUpdated = false;
}
