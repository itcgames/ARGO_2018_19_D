//#include "Level.h"
//#include <iostream>
//
//Level::Level()
//{
//}
//
//Level::~Level()
//{
//}
//
//bool Level::load(const std::string filepath)
//{
//	if (m_map.load(filepath)) {
//		tmx::Vector2u tileCount = m_map.getTileCount();
//		m_rows = tileCount.y;
//		m_cols = tileCount.x;
//
//		tmx::Vector2u tileSize = m_map.getTileSize();
//		m_tileWidth = tileSize.x;
//		m_tileHeight = tileSize.y;
//
//		auto & map_tilesets = m_map.getTilesets();
//		for (auto & tset : map_tilesets) {
//			SDL_Texture tex;
//			//if the tileset texture is loaded place it into the map with key being gid
//			if (tex.loadFromFile(tset.getImagePath())) {
//				std::cout << "Path: " << tset.getImagePath() << std::endl;
//				m_tilesets.insert(std::pair<unsigned int, SDL_Texture*>(tset.getFirstGID(), tex));
//			}
//			else {
//				std::cout << "ERROR: FAILED LOADING TILESET" << tset.getImagePath() << std::endl;
//			}
//
//		}
//
//		for (int i = 0; i < m_rows; i++) {
//			m_tiles.push_back(std::vector<Tile*>());
//			m_tiles[i].resize(m_cols);
//		}
//
//		auto & map_layers = m_map.getLayers();
//		int layerNum = -1;
//		for (auto & layer : map_layers) {
//			layerNum += 1;
//			switch (layer->getType()) {
//			case tmx::Layer::Type::Tile:
//				std::cout << "Tile Layer: " << layerNum << std::endl;
//				parseTMXTileLayer(layer, layerNum);
//				continue;
//			case tmx::Layer::Type::Object:
//				std::cout << "Object Layer: " << layerNum << std::endl;
//				parseTMXObjectLayer(layer, layerNum);
//				continue;
//			case tmx::Layer::Type::Image:
//				std::cout << "Image Layer" << layerNum++ << std::endl;
//				continue;
//			default:
//				std::cout << "ERROR: FAILED TO LOAD A VALID LAYER AT LAYER: " << layerNum << std::endl;
//				continue;
//			}
//		}
//		return true;
//	};
//	return false;
//}
//
//void Level::parseTMXTileLayer(const std::unique_ptr<tmx::Layer>& layer, int layerNum)
//{
//	// Get the current tile layer
//	auto* tile_layer = dynamic_cast<const tmx::TileLayer*>(layer.get());
//
//	//get all the tiles in the current tile layer.
//	auto & layer_tiles = tile_layer->getTiles();
//	//@debug
//	//std::cout << "Got all tiles" << std::endl;
//
//	//For every tile at poistion do something
//	int count = 0;
//	for (auto y = 0; y < m_rows; ++y) {
//		for (auto x = 0; x < m_cols; ++x) {
//			int tile_index = x + (y * m_cols);
//
//			//get the gid of the current tile
//			int cur_gid = layer_tiles[tile_index].ID;
//			//std::cout << "cur_gid: " << cur_gid << std::endl;
//			//@debug
//			//std::cout << "Gid of tile:" << cur_gid << std::endl;
//
//			//GID of 0 is an empty tile so we skip it
//			if (cur_gid == 0)
//				continue;
//
//			//Probabaly won't be a lot of tilsets
//			short tset_gid = -1;
//			//if a valid tileset is found break
//			for (auto & ts : m_tilesets) {
//				if (ts.first <= cur_gid) {
//					tset_gid = ts.first;
//				}
//			}
//
//			//if not valid skip the tile
//			if (tset_gid == -1)
//				continue;
//			//Normalize the GID(converts it to a 1 to n range instead of an n to m range)
//			cur_gid -= tset_gid;
//
//			//@debug
//			//std::cout << "Normalised GID:" << cur_gid << std::endl;
//
//			unsigned int ts_width = m_tilesets.at(tset_gid).getSize().x;
//			unsigned int ts_height = m_tilesets.at(tset_gid).getSize().y;
//
//			//Calculate the area on the tilesheet to draw
//			uint32_t region_x = (cur_gid % (ts_width / m_tileWidth))  * m_tileWidth;
//			uint32_t region_y = (cur_gid / (ts_width / m_tileHeight)) * m_tileHeight;
//
//			//Calculate the world position of the tile
//			int x_pos = x * m_tileWidth;
//			int y_pos = y * m_tileHeight;
//
//			//	//@debug
//			//	//std::cout << "added tile to the level tiles" << std::endl;
//			//}
//			bool obstacle = tile_layer->getName() == "Wall";
//			Tile * t = new Tile(m_tilesets.at(tset_gid),
//				sf::Vector2f(x_pos, y_pos),
//				sf::IntRect(region_x, region_y, m_tileWidth, m_tileHeight),
//				obstacle
//			);
//			//t->m_index = tile_index;
//			m_tiles[y][x] = t;
//			count++;
//		}
//	}
//	std::cout << "Loaded Count" << count << std::endl;
//}
//
//void Level::parseTMXObjectLayer(const std::unique_ptr<tmx::Layer>& layer, int layerNum)
//{
//	auto* object_layer = dynamic_cast<const tmx::ObjectGroup*>(layer.get());
//	auto & layer_objects = object_layer->getObjects();
//
//	std::cout << "Name: " << object_layer->getName();
//	for (auto & object : layer_objects) {
//		if (object.getName() != "Example") {
//			uint32_t object_uid = object.getUID();
//			const tmx::FloatRect object_aabb = object.getAABB();
//
//			sf::Vector2f pos = sf::Vector2f(object.getPosition().x, object.getPosition().y);
//			sf::FloatRect rect = sf::FloatRect(object_aabb.left, object_aabb.top, object_aabb.width, object_aabb.height);
//			bool trigger = false;
//			if (object.getType() == "Trigger")
//				trigger = true;
//		}
//	}
//}
