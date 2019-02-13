#include "LevelManager.h"

LevelManager::LevelManager()
{
	m_currentLevel = 0;
}

LevelManager::~LevelManager()
{
}

void LevelManager::update(const float dt)
{
}

void LevelManager::render(SDL_Renderer * renderer, Camera & camera)
{
	m_levels[m_currentLevel]->render(renderer, camera);
}

void LevelManager::loadCurrentLevel(ResourceManager & resourceManager)
{
	m_levels[m_currentLevel]->load(m_levelPaths[m_currentLevel], &resourceManager);
}

void LevelManager::parseLevelSystem(const std::string & filepath, b2World & world, const float worldScale)
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
		m_levels[i] = new Level(world, worldScale);
	}
	levelFile.close();
}
