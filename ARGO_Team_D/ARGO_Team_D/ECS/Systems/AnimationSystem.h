#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "System.h"
#include <vector>
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"

struct AnimationComponents {
	SpriteComponent * sprite;
	AnimationComponent * animation;
};

class AnimationSystem : public System {
public:
	AnimationSystem();
	void addEntity(Entity * e) override;
	void update(const float & dt);
	void removeEntity(const int id) override;
protected:
	std::vector<std::string> m_allowedtypes;
	std::map<int, AnimationComponents> m_components;
};

#endif //!ANIMATIONSYSTEM_H