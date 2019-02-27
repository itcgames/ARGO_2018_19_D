#ifndef LEVEL_H
#define LEVEL_H

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Object.hpp>

#include <SDL.h>
#include <SDL_ttf.h>
#include <map>
#include <vector>

#include "../Resource Manager/ResourceManager.h"
#include "../Camera.h"
#include "../Utils/PhysicsBody.h"
#include "../Utils/TutorialTrigger.h"
#include "../ECS/Components/AiComponent.h"
#include "../Factories/EnemyFactory.h"
#include "Goal.h"

struct TileData 
{
	int destX;
	int destY;
	unsigned int srcX;
	unsigned int srcY;
	SDL_Texture * texture;
	b2BodyDef bodyDef;
	b2Body * body = nullptr;
	b2PolygonShape shape;
	b2FixtureDef fixture;
	bool destructible;
};

struct BackgroundData 
{
	SDL_Texture* texture;
	float xPosition;
};

class Level {
public:
	// Public Functions
	Level(b2World & world, const float worldScale, TTF_Font * font, std::vector<Enemy *> & gunEnemies, std::vector<Enemy *> & flyEnemies, std::vector<Enemy *> & bigEnemies);
	~Level();
	bool load(const std::string filepath, ResourceManager * rManager, SDL_Renderer * renderer);
	void parseTMXTileLayer(const std::unique_ptr<tmx::Layer> & layer, int layerNum);
	void parseTMXObjectLayer(const std::unique_ptr<tmx::Layer> & layer, int layerNum, SDL_Renderer * renderer);
	void render(SDL_Renderer * renderer, Camera &camera);
	void createBody(float startX, float startY, float width);
	void clearPhysicsBodies();
	void clearTutorials();
	void clearEnemies();
	void clearSingleEnemy(Enemy * enemy);
	void unload();
	void update(float dt);

	// Public Members
	b2World & m_refWorld;
	float m_worldScale;
	int m_rows;
	int m_cols;
	uint32_t m_tileWidth;
	uint32_t m_tileHeight;
	std::map<unsigned int, SDL_Texture*> m_tilesets;
	std::vector<std::vector<TileData*>> m_tiles;
	tmx::Map m_map;
	std::vector<PhysicsBody *> m_physicsBodies;
	std::vector<TutorialTrigger*> m_tutorials;
	SDL_Rect m_goal;

	Goal * m_goalObj = nullptr;

	VectorAPI m_startPos;
	TTF_Font * m_font;
	std::vector<Enemy *> & m_gunEnemies;
	std::vector<Enemy *> & m_flyEnemies;
	std::vector<Enemy *> & m_bigEnemies;


	std::vector<SDL_Texture*> m_backgrounds;

	std::vector<BackgroundData> m_backs;

	// How many times to render the background
	int m_levelWidth = 3;
	SDL_Color m_backgroundColour;
};

#endif // !LEVEL_H
