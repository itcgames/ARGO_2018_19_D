#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <map>
#include "ImageResource.h"
#include "SoundResource.h"
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Resource Manager class.
// Creates Resources.
// Loads paths and id's from json.
// Stores them in cache.
// Returns a pointer to the cached asset.
class ResourceManager
{
public:
	ResourceManager(SDL_Renderer * renderer);
	~ResourceManager();

	void loadFromJson();

	void addImageResource(ImageResource* resource, const std::string& name, const char * path);
	void addSoundResource(SoundResource* resource, const std::string& name, const char * path);

	SDL_Texture * getImageResource(const std::string& name) {
		return (m_imageResources.find(name)->second->getTexture());
	}

	Mix_Music * getSoundResource(const std::string& name) {
		return (m_soundResources.find(name)->second->getSound());
	}

	bool checkLoaded();

private:
	std::map<std::string, ImageResource*> m_imageResources;
	std::map<std::string, SoundResource*> m_soundResources;

	SDL_Renderer * m_renderer;

	std::map<std::string, std::string> m_jsonImageFile;
	std::map<std::string, std::string> m_jsonSoundFile;
};

#endif 