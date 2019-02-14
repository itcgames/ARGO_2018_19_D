#ifndef CONTROLSYSTEM
#define CONTROLSYSTEM

#include <SDL.h>
#include <iostream>
#include "ECS/Components/Components.h"
#include "ECS/Systems/System.h"
#include "ECS/Components/BodyComponent.h"
#include "ECS/Components/AnimationComponent.h"
#include "Utils/VectorAPI.h"
#include <functional>   // std::function, std::negate
#include "../ECS/Components/PositionComponent.h"
#include "ECS/Entities/Entity.h"
#include "ECS/Components/TimeToLiveComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Components/GunComponent.h"

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
	void bindBullets(std::vector<Entity *> &bullets);

	void spawnProjectile(float x, float y);

private:
	bool m_moveRight;
	bool m_moveLeft;
	bool m_jump;
	bool m_fire;
	std::vector<ControlComponents> m_components;
	std::vector<string> allowedTypes;

	std::vector<Entity *> m_bullets;

	int direction;
	int counter = 0;

	//test
	bool shotgun = false;
};


#endif // !CONTROLSYSTEM
