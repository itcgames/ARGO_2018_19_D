#ifndef AISYSTEM_H
#define AISYSTEM_H

// Inherits
#include "System.h"

// Includes
#include "../ECS/Components/AiComponent.h"
#include "../ECS/Components/BodyComponent.h"
#include "../ECS/Components/AnimationComponent.h"
#include "../ECS/Components/SpriteComponent.h"

struct AiComponents
{
	AiComponent * ai;
	BodyComponent * body;
	AnimationComponent * animation;
	SpriteComponent * sprite;
};

class AiSystem : public System
{
public:
	AiSystem(BodyComponent * playerBody, const float SCALE);
	~AiSystem();
	void addEntity(Entity * e) override;
	void update();
	void removeEntity(const int id) override;
private:
	BodyComponent * m_playerBody;
	const float WORLD_SCALE;
	std::vector<string> m_allowedTypes;
	std::map<int, AiComponents> m_components;
};

#endif // !AISYSTEM_H
