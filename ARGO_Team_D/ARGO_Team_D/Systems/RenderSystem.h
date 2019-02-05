#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "..//Entities/Entities.h"
#include "System.h"
#include <SDL_ttf.h>
#include <string>

/// <summary>
/// Draws any entites attached to the screen.
/// </summary>
class RenderSystem : System {
public:
	void render(SDL_Renderer * renderer);

private:

};

#endif // !RENDERSYSTEM


