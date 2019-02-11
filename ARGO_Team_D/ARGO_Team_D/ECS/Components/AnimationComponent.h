#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include "Components.h"
#include "../Utils/VectorAPI.h"

#include <SDL.h>
#include <map>
#include <vector>

struct AnimationData {
	std::vector<SDL_Rect> frames;
	float m_timer;
	float m_length;
	float m_speed;
	float m_frameStep;
	int m_currentFrame;
	bool looping;
	bool active;
};

class AnimationComponent : public Component {
public:
	AnimationComponent() { 
		id = "Animation";
	};

	void update(const float dt) {
		auto & currAnimation = m_animations[m_currentAnimation];
		currAnimation.m_timer += dt;
		if (currAnimation.active && currAnimation.m_timer > currAnimation.m_frameStep * (currAnimation.m_currentFrame + 1)) {
			currAnimation.m_currentFrame++;
			if (currAnimation.m_currentFrame > currAnimation.frames.size() - 1) {
				currAnimation.m_currentFrame = 0;
				if (currAnimation.looping) {
					currAnimation.m_timer = 0;
					currAnimation.active = false;
				}
			}
		}
	};

	void addAnimation(const std::string & name, std::vector<SDL_Rect> & frames, float length = 0, float speed = 1) {
		AnimationData data;
		data.frames = frames;
		data.m_timer = 0;
		data.m_length = length;
		data.m_speed = speed;
		data.m_frameStep = length != 0 ? data.m_speed * (data.frames.size() / length) : 0;
		data.m_currentFrame = 0;
		m_animations[name] = data;
	};
private:
	std::string m_currentAnimation;
	std::map<std::string, AnimationData> m_animations;
};

#endif //!ANIMATIONCOMPONENT_H