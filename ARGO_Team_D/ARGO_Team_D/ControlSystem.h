#ifndef CONTROLSYSTEM
#define CONTROLSYSTEM

#include <SDL.h>
#include <iostream>
#include "ECS/Components/Components.h"
#include "ECS/Systems/System.h"
#include "ECS/Components/BodyComponent.h"
#include "ECS/Components/AnimationComponent.h"
#include "Utils/VectorAPI.h"

struct ControlComponents {
	BodyComponent * body;
	AnimationComponent * animation;
};

class ControlSystem : public System {
public:
	ControlSystem();
	~ControlSystem();
	void addEntity(Entity * e) override;
	void update();
	void moveRight();
	void moveLeft();
	void jump();
	void fire();

	void processInput(SDL_Event & e);
private:
	bool m_moveRight;
	bool m_moveLeft;
	bool m_jump;
	bool m_fire;
	std::vector<ControlComponents> m_components;
};


#endif // !CONTROLSYSTEM
