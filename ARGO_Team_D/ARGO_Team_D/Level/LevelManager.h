#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <vector>

#include <SDL.h>
#include <Box2D/Box2D.h>
#include "nlohmann/json.hpp"

#include "../Resource Manager/ResourceManager.h"
#include "../Camera.h"
#include "Level.h"

class LevelManager {
public:
	LevelManager();
	~LevelManager();
	void update(const float dt);
	void render(SDL_Renderer * renderer, Camera & camera);
	void loadCurrentLevel(ResourceManager & resourceManager);
	void parseLevelSystem(const std::string & filepath, b2World & world, const float worldScale);
protected:
	std::vector<std::string> m_levelPaths;
	std::vector<Level*> m_levels;
	int m_currentLevel;
};

#endif