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
	void update();
	void removeEntity(const int id) override;
private:
	// Private Functions
	void handleGroundEnemy(AiComponents & ac);
	void handleFlyEnemy(AiComponents & ac);

	// Private Members
	BulletManager * m_bulletManager;
	BodyComponent * m_playerBody;
	const float WORLD_SCALE;
	const float DISTANCE_THRESHOLD;
	std::vector<string> m_allowedTypes;
	std::map<int, AiComponents> m_components;
	LevelData *m_levelData;
	Camera * m_cam;
};

#endif // !AISYSTEM_H
