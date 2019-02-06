#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include "Components.h"
#include <SDL.h>

class AnimationComponent : public Component {
public:
	AnimationComponent() { id = "Animation"; };
private:
	SDL_Texture * m_texture;
	SDL_Rect m_srcRect;
	int m_width;
	int m_height;
	unsigned short m_currentFrame;
	float m_animationLength;
	float m_currentAnimationTime;


};

#endif //!ANIMATIONCOMPONENT_H