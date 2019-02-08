#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include "Components.h"
#include "../Utils/VectorAPI.h"

#include <SDL.h>
#include <map>
#include <vector>

class AnimationComponent : public Component {
public:
	AnimationComponent() { id = "Animation"; };
	void addAnimation(const std::string & name, std::vector<VectorAPI> & frames) {
		m_animations.insert(std::make_pair(name, frames));
	};
private:
	SDL_Texture * m_texture;
	SDL_Rect m_srcRect;
	int m_width;
	int m_height;
	unsigned short m_currentFrame;
	float m_animationLength;
	float m_currentAnimationTime;
	std::map<std::string, std::vector<VectorAPI>> m_animations;
};

#endif //!ANIMATIONCOMPONENT_H