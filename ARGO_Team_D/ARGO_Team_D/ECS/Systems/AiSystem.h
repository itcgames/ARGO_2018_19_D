#ifndef AISYSTEM_H
#define AISYSTEM_H

// Inherits
#include "System.h"

// Includes
#include "../ECS/Components/AiComponent.h"
#include "../ECS/Components/BodyComponent.h"
#include "../ECS/Components/AnimationComponent.h"
#include "../ECS/Components/SpriteComponent.h"
#include "../Bullets/BulletManager.h"
#include "../Observers/LevelData.h"
#include "../ECS/Components/ParticleEffectsComponent.h"
#include "../Camera.h"

struct AiComponents
{
	AiComponent * ai;
	BodyComponent * body;
	AnimationComponent * animation;
	SpriteComponent * sprite;
	ParticleEffectsComponent * part;
};

class AiSystem : public System
{
public:
	// Public Functions
	AiSystem(BulletManager * bulletManager, BodyComponent * playerBody, const float SCALE, LevelData* levelData, Camera & camera);
	~AiSystem();
	void addEntity(Entity * e) override;
	void update(float dt);
	void removeEntity(const int id) override;
private:
	// Private Functions
	void handleGroundEnemy(AiComponents & ac, float dt);
	void handleFlyEnemy(AiComponents & ac);

	// Private Members
	BulletManager * m_bulletManager;
	BodyComponent * m_playerBody;
	const float WORLD_SCALE;
	const float DISTANCE_THRESHOLD;
	const float GUN_ENEMY_ROF_MS;
	const float BIG_ENEMY_ROF_MS;
	const float GUN_ENEMY_SPEED;
	const float FLY_ENEMY_SPEED;
	const float BIG_ENEMY_SPEED;
	std::vector<string> m_allowedTypes;
	std::map<int, AiComponents> m_components;
	LevelData *m_levelData;
	Camera * m_cam;

	Mix_Chunk * groan = NULL;
	Mix_Chunk * shoot = NULL;
};

#endif // !AISYSTEM_H
