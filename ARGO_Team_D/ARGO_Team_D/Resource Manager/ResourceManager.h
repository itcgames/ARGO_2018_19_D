#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include "ImageResource.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void addImageResource(ImageResource* resource, const std::string& name, const char * path);

	SDL_Surface * getImageResource(const std::string& name) {
		return (m_imageResources.find(name)->second->getImage());
	}

private:
	std::map<std::string, ImageResource*> m_imageResources;

};

#endif 