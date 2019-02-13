#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "System.h"
#include <vector>

class AnimationSystem : public System {
public:
	AnimationSystem();
	void update(const float & dt);
protected:
	std::vector<std::string> m_allowedtypes;
};

#endif //!ANIMATIONSYSTEM_H