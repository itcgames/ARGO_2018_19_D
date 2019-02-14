#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>
#include <Box2D/Box2D.h>
#include "nlohmann/json.hpp"

#include "../Resource Manager/ResourceManager.h"
#include "../Camera.h"
#include "Level.h"
#include "../ECS/Entities/Entity.h"

class LevelManager {
public:
	LevelManager();
	~LevelManager();
	void update(const float dt);
	void render(SDL_Renderer * renderer, Camera & camera);
	void loadCurrentLevel(ResourceManager & resourceManager, SDL_Renderer * renderer);
	void parseLevelSystem(const std::string & filepath, b2World & world, const float worldScale, TTF_Font * font);
	void checkPlayerCollisions(Entity * e, ResourceManager & rm, const float worldScale, SDL_Renderer * renderer);
protected:
	TTF_Font * m_font;
	std::vector<std::string> m_levelPaths;
	std::vector<Level*> m_levels;
	int m_currentLevel;

};

#endif