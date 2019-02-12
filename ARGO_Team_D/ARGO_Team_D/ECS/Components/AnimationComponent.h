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
			std::cout << "Frame" << currAnimation.m_currentFrame << std::endl;
			std::cout << currAnimation.m_timer << std::endl;
			if (currAnimation.m_currentFrame > currAnimation.frames.size() - 1) {
				currAnimation.m_currentFrame = 0;
				if (currAnimation.looping) {
					currAnimation.m_timer = 0;
					currAnimation.m_currentFrame = 0;
				}
				else {
					currAnimation.active = false;
				}
			}
		}
	};

	void addAnimation(const std::string name, std::vector<SDL_Rect> & frames, float length = 0, float speed = 1, bool looping = false) {
		AnimationData data;
		data.frames = frames;
		data.m_timer = 0;
		data.m_length = length;
		data.m_speed = speed;
		data.m_frameStep = length != 0 ? length / (data.m_speed * data.frames.size()) : 0;
		data.m_currentFrame = 0;
		if (m_animations.empty()) {
			m_currentAnimation = name;
		}
		m_animations[name] = data;
		data.active = false;
		data.looping = looping;
	};

	void start() {
		m_animations[m_currentAnimation].active = true;
		m_animations[m_currentAnimation].m_currentFrame = 0;
	};

	void stop() {
		m_animations[m_currentAnimation].active = false;
		m_animations[m_currentAnimation].m_currentFrame = 0;
	};

	SDL_Rect getCurrentFrame() {
		auto & currAnimation = m_animations[m_currentAnimation];
		return currAnimation.frames[currAnimation.m_currentFrame];
	};

	void startAnimation(std::string animationName) {
		stop();
		m_currentAnimation = animationName;
		start();
	};
private:
	std::string m_currentAnimation;
	std::map<std::string, AnimationData> m_animations;
};

#endif //!ANIMATIONCOMPONENT_H