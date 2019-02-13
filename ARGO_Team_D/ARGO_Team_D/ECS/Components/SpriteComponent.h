#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "../../Resource Manager/ResourceManager.h"
#include <SDL.h>
#include "Components.h"

class SpriteComponent : public Component {
public:
	SpriteComponent() { id = "Sprite"; };
	SpriteComponent (
		const std::string & name,
		ResourceManager & resourceManager,
		const int w, const int h, 
		const float angle = 0.0f, SDL_Point * center = NULL,
		const SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE
	) :
		m_name(name),
		m_width(w),
		m_height(h),
		m_angle(angle),
		m_center(center),
		m_flip(flip)
	{
		id = "Sprite";
		m_texture = resourceManager.getImageResource(name);
	}
	int m_width;
	int m_height;
	SDL_Texture * getTexture() { return m_texture; };
	float m_angle;
	SDL_Point * m_center;
	SDL_RendererFlip m_flip;
	SDL_Rect m_srcRect;

	void setRender(bool b)
	{
		m_render = b;
	}
	bool getRender()
	{
		return m_render;
	}
private:
	std::string m_name;
	SDL_Texture * m_texture;
	bool m_render = true;
};

#endif //!SPRITECOMPONENT_H