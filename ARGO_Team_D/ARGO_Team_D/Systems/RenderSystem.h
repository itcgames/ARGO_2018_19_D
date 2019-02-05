#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "..//Entities/Entities.h"
#include <SDL_ttf.h>
#include <string>

/// <summary>
/// Draws any entites attached to the screen.
/// </summary>
class RenderSystem {
public:
	void addEntity(Entity * en);
	void render(SDL_Renderer * renderer);

private:
	vector<Entity*> m_entityList;
};

#endif // !RENDERSYSTEM


