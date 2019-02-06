#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include "ImageResource.h"
#include "SoundResource.h"


class ResourceManager
{
public:
	ResourceManager(SDL_Renderer * renderer);
	~ResourceManager();

	void addImageResource(ImageResource* resource, const std::string& name, const char * path);
	void addSoundResource(SoundResource* resource, const std::string& name, const char * path);

	SDL_Texture * getImageResource(const std::string& name) {
		return (m_imageResources.find(name)->second->getTexture());
	}

	Mix_Music * getSoundResource(const std::string& name) {
		return (m_soundResources.find(name)->second->getSound());
	}

private:
	std::map<std::string, ImageResource*> m_imageResources;
	std::map<std::string, SoundResource*> m_soundResources;

	SDL_Renderer * m_renderer;

};

#endif 