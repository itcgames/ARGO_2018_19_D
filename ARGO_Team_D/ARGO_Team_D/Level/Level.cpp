#include "Level.h"
#include <iostream>


Level::Level(b2World & world, float worldScale)
	: m_refWorld(world),
	m_worldScale(worldScale)
{
}

Level::~Level()
{
}

/// <summary>
/// Load a level from a tmxfile into game tiles, can facilitate other entities later
/// Resource manager is used to load a nd store tilesets for future use, as well as local storing of textures
/// </summary>
/// <param name="filepath">Filepath for the level file</param>
/// <param name="rManager">Pointer to the resource manager to handle texture loading</param>
/// <returns></returns>
bool Level::load(const std::string filepath, ResourceManager * rManager)
{
	if (m_map.load(filepath)) {
		tmx::Vector2u tileCount = m_map.getTileCount();
		m_rows = tileCount.y;
		m_cols = tileCount.x;

		tmx::Vector2u tileSize = m_map.getTileSize();
		m_tileWidth = tileSize.x;
		m_tileHeight = tileSize.y;

		auto & map_tilesets = m_map.getTilesets();
		for (auto & tset : map_tilesets) {
			rManager->addImageResource(new ImageResource, tset.getName(), tset.getImagePath().c_str());
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
				parseTMXObjectLayer(layer, layerNum);
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
	//@debug
	//std::cout << "Got all tiles" << std::endl;

	//For every tile at poistion do something
	int count = 0;
	for (auto y = 0; y < m_rows; ++y) {
		for (auto x = 0; x < m_cols; ++x) {
			int tile_index = x + (y * m_cols);

			//get the gid of the current tile
			int cur_gid = layer_tiles[tile_index].ID;
			//std::cout << "cur_gid: " << cur_gid << std::endl;
			//@debug
			//std::cout << "Gid of tile:" << cur_gid << std::endl;

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

			//@debug
			//std::cout << "Normalised GID:" << cur_gid << std::endl;

			int ts_width = 0;
			int ts_height = 0;

			SDL_QueryTexture(m_tilesets.at(tset_gid), NULL, NULL, &ts_width, & ts_height);

			//Calculate the area on the tilesheet to draw
			uint32_t region_x = (cur_gid % (ts_width / m_tileWidth))  * m_tileWidth;
			uint32_t region_y = (cur_gid / (ts_width / m_tileHeight)) * m_tileHeight;

			//Calculate the world position of the tile
			int x_pos = x * m_tileWidth;
			int y_pos = y * m_tileHeight;

			//	//@debug
			//	//std::cout << "added tile to the level tiles" << std::endl;
			//}
			TileData * t = new TileData();
			t->destX = x_pos;
			t->destY = y_pos;
			t->srcX = region_x;
			t->srcY = region_y;
			t->texture = m_tilesets.at(tset_gid);
			addBodyToTile(t, x_pos, y_pos); // Add a static body to the tile for Box2D physics
			m_tiles[y][x] = t;
			//t->m_index = tile_index;
			count++;
		}
	}
	std::cout << "Loaded Count: " << count << std::endl;
}

/// <summary>
/// Parse a tmx object layer with the ability to support tags
/// </summary>
/// <param name="layer"></param>
/// <param name="layerNum"></param>
void Level::parseTMXObjectLayer(const std::unique_ptr<tmx::Layer>& layer, int layerNum)
{
	auto* object_layer = dynamic_cast<const tmx::ObjectGroup*>(layer.get());
	auto & layer_objects = object_layer->getObjects();

	std::cout << "Name: " << object_layer->getName();
	for (auto & object : layer_objects) {
		if (object.getName() != "Example") {
			uint32_t object_uid = object.getUID();
			const tmx::FloatRect object_aabb = object.getAABB();
		}
	}
}

/// <summary>
/// Render all tile objects that exist in the level
/// </summary>
/// <param name="renderer"></param>
void Level::render(SDL_Renderer * renderer, Camera &camera)
{
	int tileC = 0;
	int tileD = 0;
	SDL_Rect destRect;
	SDL_Rect srcRect;
	SDL_Rect bounds = camera.getBounds();


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
	//std::cout << tileD << "/" << tileC << " tiles Shown with bounds of: " << bounds.x << "," << bounds.y  << "," << bounds.w << "," << bounds.h << std::endl;
}

/// <summary>
/// Create a Box2D body for a tile for collision physics
/// </summary>
/// <param name="t">A pointer to the tile</param>
/// <param name="x">The top left X position of the tile</param>
/// <param name="y">The top left Y position of the tile</param>
void Level::addBodyToTile(TileData * t, int x, int y)
{
	t->bodyDef.type = b2_staticBody; // All tiles are static
	t->bodyDef.position = b2Vec2(((x + (m_tileWidth / 2.f)) / m_worldScale), ((y + (m_tileHeight / 2.f)) / m_worldScale)); // Box2D coordinates are at the centre so we must add dimensions
	t->body = m_refWorld.CreateBody(&t->bodyDef);
	t->shape.SetAsBox((m_tileWidth / 2.f) / m_worldScale, (m_tileHeight / 2.f) / m_worldScale);
	t->fixture.density = 1.f;
	t->fixture.friction = 0.1f; // Subject to change
	t->fixture.restitution = 0.f;
	t->fixture.shape = &t->shape;
	t->body->CreateFixture(&t->fixture);
	t->body->SetFixedRotation(true);
}
