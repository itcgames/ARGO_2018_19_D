#include "Level.h"
#include <iostream>


Level::Level(b2World & world, float worldScale, TTF_Font * font, std::vector<Enemy *> & gunEnemies, std::vector<Enemy *> & flyEnemies, std::vector<Enemy *> & bigEnemies)
	: m_refWorld(world),
	m_worldScale(worldScale),
	m_font(font), 
	m_gunEnemies(gunEnemies),
	m_flyEnemies(flyEnemies),
	m_bigEnemies(bigEnemies)
{
}

Level::~Level()
{
	unload();
}

/// <summary>
/// Load a level from a tmxfile into game tiles, can facilitate other entities later
/// Resource manager is used to load a nd store tilesets for future use, as well as local storing of textures
/// </summary>
/// <param name="filepath">Filepath for the level file</param>
/// <param name="rManager">Pointer to the resource manager to handle texture loading</param>
/// <returns></returns>
bool Level::load(const std::string filepath, ResourceManager * rManager, SDL_Renderer * renderer)
{
	unload();
	if (nullptr == m_goalObj)
	{
		m_goalObj = new Goal(rManager);
	}
	if (filepath.find("Level2") != string::npos) {
		m_backgrounds.push_back(rManager->getImageResource("Background2"));
		m_backgrounds.push_back(rManager->getImageResource("Background2-2"));
		m_backgrounds.push_back(rManager->getImageResource("Background2-3"));
	}
	else if(filepath.find("Level3") != string::npos)
	{
		m_backgrounds.push_back(rManager->getImageResource("Background3"));
		m_backgrounds.push_back(rManager->getImageResource("Background3-2"));
		m_backgrounds.push_back(rManager->getImageResource("Background3-3"));
	}
	else
	{
		m_backgrounds.push_back(rManager->getImageResource("Background1"));
		m_backgrounds.push_back(rManager->getImageResource("Background1-2"));
		m_backgrounds.push_back(rManager->getImageResource("Background1-3"));
	}
	std::cout << m_backgrounds.size() << std::endl;

	if (m_map.load(filepath)) {
		tmx::Vector2u tileCount = m_map.getTileCount();
		m_rows = tileCount.y;
		m_cols = tileCount.x;

		tmx::Vector2u tileSize = m_map.getTileSize();
		m_tileWidth = tileSize.x;
		m_tileHeight = tileSize.y;

		auto & map_tilesets = m_map.getTilesets();
		for (auto & tset : map_tilesets) {
			//rManager->addImageResource(new ImageResource, tset.getName(), tset.getImagePath().c_str());
			//if the tileset texture is loaded place it into the map with key being gid
			SDL_Texture * tex = rManager->getImageResource(tset.getName());
			if (tex) {
				std::cout << "Path: " << tset.getImagePath() << std::endl;
				m_tilesets.insert(std::pair<unsigned int, SDL_Texture*>(tset.getFirstGID(), tex));
			}
			else {
				std::cout << "ERROR: FAILED LOADING TILESET" << tset.getImagePath() << std::endl;
			}

		}

		// Resize The vector to be an initial grid size (prevents expensive copy operations)
		for (int i = 0; i < m_rows; i++) {
			m_tiles.push_back(std::vector<TileData*>());
			m_tiles[i].resize(m_cols);
		}

		auto & map_layers = m_map.getLayers();
		int layerNum = -1;
		for (auto & layer : map_layers) {
			layerNum += 1;
			switch (layer->getType()) {
			case tmx::Layer::Type::Tile:
				std::cout << "Tile Layer: " << layerNum << std::endl;
				parseTMXTileLayer(layer, layerNum);
				continue;
			case tmx::Layer::Type::Object:
				std::cout << "Object Layer: " << layerNum << std::endl;
				parseTMXObjectLayer(layer, layerNum, renderer);
				continue;
			case tmx::Layer::Type::Image:
				std::cout << "Image Layer" << layerNum++ << std::endl;
				continue;
			default:
				std::cout << "ERROR: FAILED TO LOAD A VALID LAYER AT LAYER: " << layerNum << std::endl;
				continue;
			}
		}
		return true;
	};
	return false;
}

/// <summary>
/// Parse a tmx tile layer into TileData structs
/// </summary>
/// <param name="layer">The current layer to be parsed, mainly for debug parsing</param>
/// <param name="layerNum"></param>
void Level::parseTMXTileLayer(const std::unique_ptr<tmx::Layer>& layer, int layerNum)
{
	// Get the current tile layer
	auto* tile_layer = dynamic_cast<const tmx::TileLayer*>(layer.get());

	//get all the tiles in the current tile layer.
	auto & layer_tiles = tile_layer->getTiles();

	//For every tile at poistion do something
	auto props = tile_layer->getProperties();
	bool destructible = std::find_if(props.begin(), props.end(), [](tmx::Property & p) {
		if (p.getName() == "Destructible") {
			if (p.getBoolValue()) {
				return true;
			}
		}
		return false;

	}) != props.end();
	int count = 0;
	for (auto y = 0; y < m_rows; ++y) {
		for (auto x = 0; x < m_cols; ++x) {
			int tile_index = x + (y * m_cols);

			//get the gid of the current tile
			int cur_gid = layer_tiles[tile_index].ID;

			//GID of 0 is an empty tile so we skip it
			if (cur_gid == 0)
				continue;

			//Probabaly won't be a lot of tilsets
			short tset_gid = -1;
			//if a valid tileset is found break
			for (auto & ts : m_tilesets) {
				if (ts.first <= cur_gid) {
					tset_gid = ts.first;
				}
			}

			//if not valid skip the tile
			if (tset_gid == -1)
				continue;
			//Normalize the GID(converts it to a 1 to n range instead of an n to m range)
			cur_gid -= tset_gid;

			int ts_width = 0;
			int ts_height = 0;

			SDL_QueryTexture(m_tilesets.at(tset_gid), NULL, NULL, &ts_width, & ts_height);

			//Calculate the area on the tilesheet to draw
			uint32_t region_x = (cur_gid % (ts_width / m_tileWidth))  * m_tileWidth;
			uint32_t region_y = (cur_gid / (ts_width / m_tileHeight)) * m_tileHeight;

			//Calculate the world position of the tile
			int x_pos = x * m_tileWidth;
			int y_pos = y * m_tileHeight;

			TileData * t = new TileData();
			t->destX = x_pos;
			t->destY = y_pos;
			t->srcX = region_x;
			t->srcY = region_y;
			t->texture = m_tilesets.at(tset_gid);
			t->destructible = destructible;
			m_tiles[y][x] = t;
			count++;
		}
	}
	for (auto y = 0; y < m_rows; ++y)
	{
		float xPos, yPos, width = 0;
		bool bodyStarted = false;
		for (auto x = 0; x < m_cols; ++x)
		{
			if (nullptr != m_tiles[y][x])
			{
				if (!bodyStarted)
				{
					bodyStarted = true;
					xPos = m_tiles[y][x]->destX;
					yPos = m_tiles[y][x]->destY;
					width = m_tileWidth;
				}
				else
				{
					width += m_tileWidth;
				}
				if (x == m_cols - 1) {
					bodyStarted = false;
					createBody(xPos, yPos, width);
				}
			}
			else if(bodyStarted)
			{
				bodyStarted = false;
				createBody(xPos, yPos, width);
			}
		}
	}
	std::cout << "Loaded Count: " << count << std::endl;
}

/// <summary>
/// Parse a tmx object layer with the ability to support tags
/// </summary>
/// <param name="layer"></param>
/// <param name="layerNum"></param>
void Level::parseTMXObjectLayer(const std::unique_ptr<tmx::Layer>& layer, int layerNum, SDL_Renderer * renderer)
{
	auto* object_layer = dynamic_cast<const tmx::ObjectGroup*>(layer.get());
	auto & layer_objects = object_layer->getObjects();

	int gunEnemyCounter = 0;
	int flyEnemyCounter = 0;
	int bigEnemyCounter = 0;

	std::cout << "Name: " << object_layer->getName();
	for (auto & object : layer_objects) {
		std::string type = object.getType();
		if (type == "PlayerSpawn") {
			auto pos = object.getPosition();
			m_startPos.x = pos.x;
			m_startPos.y = pos.y;
		}
		else if (type == "Goal") {
			auto rect = object.getAABB();
			m_goal = { (int)rect.left, (int)rect.top, (int)rect.width, (int)rect.height };
			m_goalObj->setCollisionRect((int)rect.left, (int)rect.top, (int)rect.width, (int)rect.height);
			m_goalObj->setPosition((int)rect.left, (int)rect.top);
		}
		else if (type == "TutorialTrigger") {
			auto rect = object.getAABB();
			auto rotation = object.getRotation();
			auto t = new TutorialTrigger(
				rect.left,
				rect.top,
				rect.width,
				rect.height,
				rotation, 
				m_worldScale,
				m_refWorld
			);
			m_tutorials.push_back(t);
		}
		else if (type == "TutorialPoint") {
			auto & props = object.getProperties();
			auto id = std::find_if(props.begin(), props.end(), [](const tmx::Property & p) {
				return p.getName() == "RelativeTriggerID";
			});
			if (id != props.end()) {
				auto tutorial = m_tutorials.at(id->getIntValue() - 1);
				auto & bounds = tutorial->promptBounds;

				auto loadedBounds = object.getAABB();
				bounds = { (int)loadedBounds.left, (int)loadedBounds.top, (int)loadedBounds.width, (int)loadedBounds.height };
				tutorial->originalSizeV = VectorAPI(bounds.w, bounds.h);
				auto message = std::find_if(props.begin(), props.end(), [](const tmx::Property & p) {
					return p.getName() == "Message";
				});
				tutorial->message = message->getStringValue();
				SDL_Color col = { 255,0,0,255 };
				tutorial->messageSurface = TTF_RenderText_Blended_Wrapped(m_font, tutorial->message.c_str(), col, bounds.w);
				tutorial->messageTexture = SDL_CreateTextureFromSurface(renderer, tutorial->messageSurface);
				std::cout << "Tutorial: " << id->getIntValue() << " Message: " << tutorial->message << std::endl;
			}
		}
		else if (type.find("Enemy") != std::string::npos)
		{
			auto pos = object.getPosition();
			auto properties = object.getProperties();
			int min = 0;
			int max = 0;
			for (auto & prop : properties)
			{
				string name = prop.getName();
				if (name == "MinX")
				{
					min = std::stoi(prop.getStringValue());
				}
				else if (name == "MaxX")
				{
					max = std::stoi(prop.getStringValue());
				}
			}
			if (type == "GunEnemy")
			{
				auto body = m_gunEnemies.at(gunEnemyCounter)->body->getBody();
				b2Vec2 newPos = b2Vec2(pos.x / m_worldScale, pos.y / m_worldScale);
				body->SetTransform(newPos, body->GetAngle());
				m_gunEnemies.at(gunEnemyCounter)->body->setInitialPos(newPos);
				m_gunEnemies.at(gunEnemyCounter)->ai->setMovementMarkers(min, max);
				m_gunEnemies.at(gunEnemyCounter)->ai->setActivationState(true);
				++gunEnemyCounter;
			}
			else if (type == "FlyEnemy")
			{
				auto body = m_flyEnemies.at(flyEnemyCounter)->body->getBody();
				b2Vec2 newPos = b2Vec2(pos.x / m_worldScale, pos.y / m_worldScale);
				body->SetTransform(newPos, body->GetAngle());
				m_flyEnemies.at(flyEnemyCounter)->body->setInitialPos(newPos);
				m_flyEnemies.at(flyEnemyCounter)->ai->setMovementMarkers(min, max);
				m_flyEnemies.at(flyEnemyCounter)->ai->setActivationState(true);
				++flyEnemyCounter;
			}
			else if (type == "BigEnemy")
			{
				auto body = m_bigEnemies.at(bigEnemyCounter)->body->getBody();
				b2Vec2 newPos = b2Vec2(pos.x / m_worldScale, pos.y / m_worldScale);
				body->SetTransform(newPos, body->GetAngle());
				m_bigEnemies.at(bigEnemyCounter)->body->setInitialPos(newPos);
				m_bigEnemies.at(bigEnemyCounter)->ai->setMovementMarkers(min, max);
				m_bigEnemies.at(bigEnemyCounter)->ai->setActivationState(true);
				++bigEnemyCounter;
			}
		}
	}
}

/// <summary>
/// Render all tile objects that exist in the level
/// </summary>
/// <param name="renderer"></param>
void Level::render(SDL_Renderer * renderer, Camera &camera)
{
	SDL_SetRenderDrawColor(renderer, m_backgroundColour.r, m_backgroundColour.g, m_backgroundColour.b, m_backgroundColour.a);
	SDL_RenderClear(renderer);
	int tileC = 0;
	int tileD = 0;
	SDL_Rect destRect;
	SDL_Rect srcRect;
	SDL_Rect bounds = camera.getBounds();

	SDL_Rect destination;
	destination.x = -1900 - bounds.x / 1.3f;
	destination.y = 0;
	destination.w = 1920;
	destination.h = 1080;

	for (int i = 0; i < m_levelWidth; i++) {
		for (int j = 0; j < 3; j++) {
			SDL_RenderCopy(renderer, m_backgrounds.at(j), NULL, &destination);
			destination.x += 1900;
		}
	}

	destRect.w = m_tileWidth;
	destRect.h = m_tileHeight;

	srcRect.w = m_tileWidth;
	srcRect.h = m_tileHeight;

	for (auto & row : m_tiles) {
		for (auto tileData : row) {
			if (tileData) {
				tileC++;
				int tdX = tileData->destX;
				int tdY = tileData->destY;
				if (tdX + destRect.w < bounds.x || tdX > bounds.x + bounds.w ||
					tdY + destRect.h < bounds.y || tdY > bounds.y + bounds.h) {
					continue;
				}
				tileD++;
				destRect.x = tileData->destX - bounds.x;
				destRect.y = tileData->destY - bounds.y;
				srcRect.x = tileData->srcX;
				srcRect.y = tileData->srcY;
				SDL_RenderCopy(renderer, tileData->texture, &srcRect, &destRect);
			}
		}
	}
	Uint8 r = 0, g = 0, b = 0, a = 0;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
	for (auto & tutorial : m_tutorials) {
		SDL_Rect rect = tutorial->promptBounds;
		rect.x -= bounds.x;
		rect.y -= bounds.y;
		SDL_RenderCopy(renderer, tutorial->messageTexture, NULL, &rect);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &rect);

		SDL_Rect tRect = tutorial->bounds;
		tRect.x -= bounds.x;
		tRect.y -= bounds.y;
		SDL_RenderDrawRect(renderer, &tRect);
	}
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	m_goalObj->render(renderer, &camera);
}

/// <summary>
/// Create a Box2D body in the level that represents one or more tiles
/// </summary>
/// <param name="x">The top left X position of the body</param>
/// <param name="y">The top left Y position of the body</param>
/// <param name="t">The width of the body</param>
void Level::createBody(float x, float y, float width)
{
	PhysicsBody  * pb = new PhysicsBody("PhysicsBody");
	pb->bodyDef.type = b2_staticBody;
	pb->bodyDef.position = b2Vec2((x + (width / 2.f)) / m_worldScale, (y + (m_tileHeight / 2.f)) / m_worldScale);
	pb->body = m_refWorld.CreateBody(&pb->bodyDef);
	pb->shape.SetAsBox((width / 2.f) / m_worldScale, (m_tileHeight / 2.f) / m_worldScale);
	pb->fixture.density = 1.f;
	pb->fixture.friction = 0.f;
	pb->fixture.shape = &pb->shape;
	pb->fixture.filter.categoryBits = 0x0008;
	pb->data.data = pb;
	pb->fixture.userData = &pb->data;
	pb->body->CreateFixture(&pb->fixture);
	pb->body->SetFixedRotation(true);
	m_physicsBodies.push_back(pb);
}

/// <summary>
/// Function used to properly clear all Box2D bodies from a level
/// </summary>
void Level::clearPhysicsBodies()
{
	for (auto & pb : m_physicsBodies)
	{
		m_refWorld.DestroyBody(pb->body);
		delete pb;
	}
	m_physicsBodies.clear();
}

void Level::clearTutorials()
{
	for (auto tut : m_tutorials)
	{
		m_refWorld.DestroyBody(tut->pb.body);
		delete tut;
		tut = nullptr;
	}
	m_tutorials.clear();
}

void Level::clearEnemies()
{
	for (auto enemy : m_gunEnemies)
	{
		clearSingleEnemy(enemy);
	}
	for (auto enemy : m_flyEnemies)
	{
		clearSingleEnemy(enemy);
	}
	for (auto enemy : m_bigEnemies)
	{
		clearSingleEnemy(enemy);
	}
}

void Level::clearSingleEnemy(Enemy * enemy)
{
	auto body = enemy->body->getBody();
	enemy->ai->setActivationState(false);
	body->SetTransform(b2Vec2(-1000, 0), body->GetAngle());
}

void Level::unload()
{
	for (auto & row : m_tiles) {
		for (auto & tile : row) {
			if (nullptr != tile && nullptr != tile->body) {
				m_refWorld.DestroyBody(tile->body);
				delete tile;
				tile = nullptr;
			}
		}
		row.clear();
	}
	m_tiles.clear();

	/*for (auto kv : m_tilesets) {
		if (nullptr != kv.second) {
			SDL_DestroyTexture(kv.second);
		}
	}*/
	m_tilesets.clear();
	clearPhysicsBodies();
	clearTutorials();
	clearEnemies();
}

void Level::update(const float dt)
{
	for (auto & tut : m_tutorials) {
		tut->update();
	}
	m_goalObj->update(dt);
}
