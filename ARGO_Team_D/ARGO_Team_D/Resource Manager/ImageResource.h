#ifndef IMAGERESOURCE_H
#define IMAGERESOURCE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class ImageResource {
public:
	ImageResource();
	virtual ~ImageResource();

	void loadResource();
	void unloadResource();

	void setResourceId(unsigned id) { m_id = id; }
	unsigned getResourceId() const { return m_id; }

	void setResourcePath(const char* path) { m_resourcePath = path; }
	std::string getResourcePath() const { return m_resourcePath; }

	SDL_Surface * getImage() { if(m_image != nullptr) return m_image; }

protected:
	unsigned m_id;
	const char * m_resourcePath;
	SDL_Surface * m_image;

};
#endif // !IMAGERESOURCE_H

