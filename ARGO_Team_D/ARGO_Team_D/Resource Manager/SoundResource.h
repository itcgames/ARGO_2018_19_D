#ifndef SOUNDRESOURCE_H
#define SOUNDRESOURCE_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

class SoundResource {
public:
	SoundResource();
	virtual ~SoundResource();

	void loadResource();
	void unloadResource();

	void setResourceId(unsigned id) { m_id = id; }
	unsigned getResourceId() const { return m_id; }

	void setResourcePath(const char* path) { m_resourcePath = path; }
	std::string getResourcePath() const { return m_resourcePath; }

	Mix_Music * getSound() { if (m_sound != nullptr) return m_sound; }

protected:
	unsigned m_id;
	const char * m_resourcePath;
	Mix_Music *m_sound = NULL;

};
#endif // !SOUNDRESOURCE_H


