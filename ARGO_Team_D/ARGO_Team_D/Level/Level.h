#ifndef LEVEL_H
#define LEVEL_H

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Object.hpp>
#include <SDL.h>
#include <SDL_ttf.h>
#include <map>
#include <Box2D/Box2D.h>

#include "../Resource Manager/ResourceManager.h"
#include "../Camera.h"

enum _entityCategory {
	PLAYER,
	TUTORIAL
};

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
	bool destructible;
};

struct PhysicsBody {
	b2BodyDef bodyDef;
	b2Body * body = nullptr;
	b2PolygonShape shape;
	b2FixtureDef fixture;
};

struct TutorialTrigger {
	TutorialTrigger(const float x, const float y, const int w, const int h, const float angle, const float worldScale, b2World & world) {
		float halfWidth = w / 2.f;
		float halfHeight = h / 2.f;
		bodyDef.position = b2Vec2((x + halfWidth) / worldScale, (y + halfHeight) / worldScale);
		body = world.CreateBody(&bodyDef);

		shape.SetAsBox(halfWidth / worldScale, halfHeight / worldScale);

		fixture.isSensor = true;
		fixture.filter.categoryBits = _entityCategory::TUTORIAL;
		fixture.filter.maskBits = _entityCategory::PLAYER;
		fixture.shape = &shape;

		body->CreateFixture(&fixture);
		body->SetTransform(b2Vec2(x, y), angle);
	};
	b2BodyDef bodyDef;
	b2Body * body = nullptr;
	b2PolygonShape shape;
	b2FixtureDef fixture;
	SDL_Rect bounds;
	std::string message;
	SDL_Surface * messageSurface;
	SDL_Texture * messageTexture;
};
class Level {
public:
	// Public Functions
	Level(b2World & world, const float worldScale, TTF_Font * font);
	~Level();
	bool load(const std::string filepath, ResourceManager * rManager, SDL_Renderer * renderer);
	void parseTMXTileLayer(const std::unique_ptr<tmx::Layer> & layer, int layerNum);
	void parseTMXObjectLayer(const std::unique_ptr<tmx::Layer> & layer, int layerNum, SDL_Renderer * renderer);
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
	std::vector<TutorialTrigger> m_tutorials;
	SDL_Rect m_goal;
	VectorAPI m_startPos;
	TTF_Font * m_font;
};

#endif // !LEVEL_H
