#include "LevelManager.h"
#include "../ECS/Components/PositionComponent.h"
#include "../ECS/Components/SpriteComponent.h"
#include "../ECS/Components/BodyComponent.h"

LevelManager::LevelManager()
{
	m_currentLevel = 0;
}

LevelManager::~LevelManager()
{
}

void LevelManager::update(const float dt)
{
	m_levels[m_currentLevel]->update(dt);
}

void LevelManager::render(SDL_Renderer * renderer, Camera & camera)
{
	m_levels[m_currentLevel]->render(renderer, camera);
}

void LevelManager::loadCurrentLevel(ResourceManager & resourceManager, SDL_Renderer * renderer)
{
	m_levels[m_currentLevel]->load(m_levelPaths[m_currentLevel], &resourceManager, renderer);
}

void LevelManager::parseLevelSystem(const std::string & filepath, b2World & world, const float worldScale, TTF_Font * font, std::vector<Enemy *> & gunEnemies, std::vector<Enemy *> & flyEnemies, std::vector<Enemy *> & bigEnemies)
{
	using json = nlohmann::json;
	std::ifstream levelFile(filepath);
	json jFile = json::parse(levelFile);

	std::map<std::string, std::vector<std::string>> jsonLevelFile = jFile;
	for (auto & fp : jsonLevelFile["LevelSystem"]) {
		m_levelPaths.push_back(fp);
	}
	m_levels.resize(m_levelPaths.size());
	for (int i = 0; i < m_levelPaths.size(); ++i) {
		m_levels[i] = new Level(world, worldScale, font, gunEnemies, flyEnemies, bigEnemies);
	}
	levelFile.close();
}

bool LevelManager::checkPlayerCollisions(Entity * e, ResourceManager & rm, const float worldScale, SDL_Renderer * renderer)
{
	std::vector<std::string> allowedTypes = {"Position", "Sprite", "Body"};
	auto comps = e->getComponentsOfType(allowedTypes);
	if (comps.size() == allowedTypes.size()) {
		auto pos = dynamic_cast<PositionComponent *>(comps["Position"]);
		auto sprite = dynamic_cast<SpriteComponent*>(comps["Sprite"]);
		auto body = dynamic_cast<BodyComponent*>(comps["Body"]);
		auto p = pos->getPosition();
		auto goal = m_levels[m_currentLevel]->m_goal;
		if (p.x + sprite->m_width > goal.x
			&& p.x < goal.x + goal.w
			&& p.y + sprite->m_height > goal.y
			&& p.y <  goal.y + goal.h) {
			m_levels[m_currentLevel]->unload();

			if (m_currentLevel != m_levels.size() - 1) {
				m_currentLevel++;
			}
			else {
				//m_currentLevel = 0;
				finishedGame = true;
			}
			loadCurrentLevel(rm, renderer);
			auto startPos = m_levels[m_currentLevel]->m_startPos;
			pos->setPosition(startPos);
			body->getBody()->SetTransform(b2Vec2(startPos.x / worldScale, startPos.y / worldScale), 0);
			body->setInitialPos(b2Vec2(startPos.x / worldScale, startPos.y / worldScale));

			return true;
		}
	}
	return false;
}

void LevelManager::loadLevel(Entity * e,ResourceManager & resourceManager, SDL_Renderer * renderer, int level)
{

	std::vector<std::string> allowedTypes = { "Position", "Sprite", "Body" };
	auto comps = e->getComponentsOfType(allowedTypes);
	if (comps.size() == allowedTypes.size()) {
		auto pos = dynamic_cast<PositionComponent *>(comps["Position"]);
		auto sprite = dynamic_cast<SpriteComponent*>(comps["Sprite"]);
		auto body = dynamic_cast<BodyComponent*>(comps["Body"]);
		auto p = pos->getPosition();


		m_currentLevel = level;
		m_levels[m_currentLevel]->load(m_levelPaths[m_currentLevel], &resourceManager, renderer);

		auto startPos = m_levels[m_currentLevel]->m_startPos;
		pos->setPosition(startPos);
		body->getBody()->SetTransform(b2Vec2(startPos.x / 30, startPos.y / 30), 0);
	}
}

int LevelManager::getCurrentLevel()
{
	return m_currentLevel;
}

Level * LevelManager::getCurrentLevelObject()
{
	return m_levels.at(m_currentLevel);
}

void LevelManager::unloadAllLevels()
{
	for (auto level : m_levels) {
		level->unload();
	}
}

bool LevelManager::isGameFinished()
{
	return finishedGame;
}

void LevelManager::setGameFinished(bool b)
{
	finishedGame = b;
}
