#ifndef LEVEL_H
#define LEVEL_H

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Object.hpp>
#include <SDL.h>
#include <map>
#include <Box2D/Box2D.h>

#include "../Resource Manager/ResourceManager.h"
#include "../Camera.h"

struct TileData {
	int destX;
	int destY;
	unsigned int srcX;
	unsigned int srcY;
	SDL_Texture * texture;
	b2BodyDef bodyDef;
	b2Body * body = nullptr;
	b2PolygonShape shape;
	b2FixtureDef fixture;
};

struct PhysicsBody {
	b2BodyDef bodyDef;
	b2Body * body = nullptr;
	b2PolygonShape shape;
	b2FixtureDef fixture;
};

class Level {
public:
	// Public Functions
	Level(b2World & world, const float worldScale);
	~Level();
	bool load(const std::string filepath, ResourceManager * rManager);
	void parseTMXTileLayer(const std::unique_ptr<tmx::Layer> & layer, int layerNum);
	void parseTMXObjectLayer(const std::unique_ptr<tmx::Layer> & layer, int layerNum);
	void render(SDL_Renderer * renderer, Camera &camera);
	void createBody(float startX, float startY, float width);
	void clearPhysicsBodies();

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
	SDL_Rect m_goal;
	VectorAPI m_startPos;
};

#endif // !LEVEL_H
