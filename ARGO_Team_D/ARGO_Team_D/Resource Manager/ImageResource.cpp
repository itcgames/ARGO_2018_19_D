#include "ImageResource.h"

ImageResource::ImageResource()
{
}

ImageResource::~ImageResource()
{
}

void ImageResource::loadResource()
{
	m_image = IMG_Load(m_resourcePath);
}

void ImageResource::unloadResource()
{
}
