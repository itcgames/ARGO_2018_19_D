#ifndef IMAGERESOURCE_H
#define IMAGERESOURCE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class ImageResource {
public:
	ImageResource();
	virtual ~ImageResource();

	void loadResource(SDL_Renderer * renderer);
	void unloadResource();

	void setResourceId(unsigned id) { m_id = id; }
	unsigned getResourceId() const { return m_id; }

	void setResourcePath(const char* path) { m_resourcePath = path; }
	std::string getResourcePath() const { return m_resourcePath; }

	SDL_Texture * getTexture() { if(m_texture != nullptr) return m_texture; }

protected:
	unsigned m_id;
	const char * m_resourcePath;
	SDL_Surface * m_image;
	SDL_Texture * m_texture;

};
#endif // !IMAGERESOURCE_H

