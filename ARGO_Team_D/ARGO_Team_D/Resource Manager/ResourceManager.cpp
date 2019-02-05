#include "ResourceManager.h"

ResourceManager::ResourceManager(SDL_Renderer * renderer)
{
	m_renderer = renderer;
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::addImageResource(ImageResource * resource, const std::string & name, const char * path)
{
	resource->setResourcePath(path);
	resource->setResourceId(m_imageResources.size());
	resource->loadResource(m_renderer);

	m_imageResources.insert(std::pair<std::string, ImageResource*>(name, resource));
}

void ResourceManager::addSoundResource(SoundResource * resource, const std::string & name, const char * path)
{
	resource->setResourcePath(path);
	resource->setResourceId(m_soundResources.size());
	resource->loadResource();

	m_soundResources.insert(std::pair<std::string, SoundResource*>(name, resource));
}
