#ifndef CONTROLSYSTEM
#define CONTROLSYSTEM

#include <SDL.h>
#include <iostream>
#include <functional>   // std::function, std::negate
#include "../ECS/Components/Components.h"
#include "../ECS/Systems/System.h"
#include "../ECS/Components/BodyComponent.h"
#include "../ECS/Components/SpriteComponent.h"
#include "../ECS/Components/AnimationComponent.h"
#include "../ECS/Components/PositionComponent.h"
#include "../ECS/Components/HealthComponent.h"
#include "../ECS/Entities/Entity.h"
#include "../Utils/VectorAPI.h"
#include "../Bullets/BulletManager.h"
#include "../ECS/Components/ParticleEffectsComponent.h"

struct ControlComponents {
	BodyComponent * body;
	AnimationComponent * animation;
	ParticleEffectsComponent * part;
	SpriteComponent * sprite;
	HealthComponent * health;
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

	void bindBullets(BulletManager * bulletManager);
	void bindJump(Mix_Chunk * sound);
	void spawnProjectile(float x, float y);
	void removeEntity(const int id) override;
private:
	bool m_moveRight;
	bool m_moveLeft;
	bool m_jump;
	bool m_fire;
	std::map<int, ControlComponents> m_components;
	std::vector<string> allowedTypes;

	//std::vector<Entity *> m_bullets;
	BulletManager * m_bulletManager;

	int direction;
	int counter = 0;

	//test
	bool shotgun = false;


	Mix_Chunk * jumpSound = NULL;
};


#endif // !CONTROLSYSTEM
