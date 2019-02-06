#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../Entities/Entity.h"
#include "System.h"

/// <summary>
/// Draws any entites attached to the screen.
/// </summary>
class RenderSystem : public System {
public:
	void render(SDL_Renderer * renderer);

private:
	SDL_Rect dest;
	SDL_Rect src;
};

#endif // !RENDERSYSTEM


