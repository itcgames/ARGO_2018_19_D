#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

// Inherits
#include "System.h"

// Includes
#include <iostream>
#include "../Entities/Entity.h"
#include "../Camera.h"
#include "../Components/Components.h"
#include "../Components/PositionComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Utils/VectorAPI.h"

struct RenderComponents
{
	PositionComponent * position;
	SpriteComponent * sprite;
	AnimationComponent * animation;
};

/// <summary>
/// Draws any entites attached to the screen.
/// </summary>
class RenderSystem : public System {
public:
	void addEntity(Entity * e) override;
	void render(SDL_Renderer* renderer, Camera & camera);
	void removeEntity(const int id) override;
private:
	SDL_Rect dest;
	SDL_Rect src;
	std::map<int, RenderComponents> m_components;
};

#endif // !RENDERSYSTEM


