#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "..//Entities/Entities.h"
#include "System.h"

/// <summary>
/// Draws any entites attached to the screen.
/// </summary>
class RenderSystem : System {
public:
	void render(SDL_Renderer * renderer);

private:

};

#endif // !RENDERSYSTEM


