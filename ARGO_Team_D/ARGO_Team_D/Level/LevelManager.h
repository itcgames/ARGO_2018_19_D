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
#include "../Factories/EnemyFactory.h"

class LevelManager {
public:
	LevelManager();
	~LevelManager();
	void update(const float dt);
	void render(SDL_Renderer * renderer, Camera & camera);
	void loadCurrentLevel(ResourceManager & resourceManager, SDL_Renderer * renderer);
	void parseLevelSystem(const std::string & filepath, b2World & world, const float worldScale, TTF_Font * font, std::vector<Enemy *> & gunEnemies, std::vector<Enemy *> & flyEnemies, std::vector<Enemy *> & bigEnemies);
	bool checkPlayerCollisions(Entity * e, ResourceManager & rm, const float worldScale, SDL_Renderer * renderer);

	void loadLevel(Entity * e, ResourceManager & resourceManager, SDL_Renderer * renderer, int level);
	std::vector<Level*> m_levels;
	int getCurrentLevel();
	Level * getCurrentLevelObject();
	void unloadAllLevels();
	bool isGameFinished();
	void setGameFinished(bool b);
protected:
	TTF_Font * m_font;
	std::vector<std::string> m_levelPaths;
	
	int m_currentLevel;
	bool finishedGame = false;

};

#endif