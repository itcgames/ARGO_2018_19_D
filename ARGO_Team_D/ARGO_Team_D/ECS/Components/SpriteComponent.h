#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "../../Resource Manager/ResourceManager.h"
#include <SDL.h>
#include "Components.h"

class SpriteComponent : public Component {
public:
	SpriteComponent() { id = "Sprite"; };
	SpriteComponent(const std::string & name, ResourceManager & resourceManager, const int w, const int h) :
		m_name(name),
		m_width(w),
		m_height(h)
	{
		id = "Sprite";
		m_texture = resourceManager.getImageResource(name);
	};
	int m_width;
	int m_height;
	SDL_Texture * getTexture() { return m_texture; };
private:
	std::string m_name;
	SDL_Texture * m_texture;
};

#endif //!SPRITECOMPONENT_H