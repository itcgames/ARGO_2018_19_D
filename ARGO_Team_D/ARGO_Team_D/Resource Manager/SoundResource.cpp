#include "SoundResource.h"

SoundResource::SoundResource()
{
}

SoundResource::~SoundResource()
{
}

void SoundResource::loadResource()
{
	m_sound = Mix_LoadMUS(m_resourcePath);
}

void SoundResource::unloadResource()
{
}
