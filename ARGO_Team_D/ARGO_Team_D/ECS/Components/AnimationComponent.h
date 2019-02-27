#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include "Components.h"
#include "../Utils/VectorAPI.h"
#include "../FSM/Animation.h"

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
		if (m_animation.getCurrent()->m_name != m_animation.getPrevious()->m_name) {
			startAnimation(m_animation.getCurrent()->m_name);
			m_animation.setPrevious(m_animation.getCurrent());
		}
		auto & currAnimation = m_animations[m_currentAnimation];
		currAnimation.m_timer += dt;
		if (currAnimation.active && currAnimation.m_timer > currAnimation.m_frameStep * (currAnimation.m_currentFrame + 1)) {
			currAnimation.m_currentFrame++;
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
		auto & currAnimation = m_animations[m_currentAnimation];
		currAnimation.active = true;
		currAnimation.m_currentFrame = 0;
		currAnimation.m_timer = 0;
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

	void handleInput(std::string state) {
		m_animation.handle(state);
	};

	void setLooping(std::string name,bool looping) {
		if (!name.empty())
		{
			m_animations[name].looping = looping;
		}
		else {
			m_animations[m_currentAnimation].looping = looping;
		}
	}
	void setRender(bool b) 
	{
		m_render = b;
	}
	bool getRender()
	{
		return m_render;
	}
private:
	std::string m_currentAnimation;
	std::map<std::string, AnimationData> m_animations;
	Animation m_animation;
	bool m_render = true; //bool to indicate if something should be drawn or not
};

#endif //!ANIMATIONCOMPONENT_H