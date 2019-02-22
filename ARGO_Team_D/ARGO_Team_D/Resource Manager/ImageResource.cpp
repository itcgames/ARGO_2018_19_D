#include "ImageResource.h"

ImageResource::ImageResource()
{
}

ImageResource::~ImageResource()
{
}

void ImageResource::loadResource(SDL_Renderer * renderer)
{
	m_image = IMG_Load(m_resourcePath);
	m_texture = SDL_CreateTextureFromSurface(renderer, m_image);
	SDL_FreeSurface(m_image);
	m_image = NULL;
}

void ImageResource::unloadResource()
{
}
