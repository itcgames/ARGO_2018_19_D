#ifndef GOAL_H
#define GOAL_H

#include <SDL.h>
#include "../Camera.h"
#include "../Resource Manager/ResourceManager.h"
#include "../ECS//Components/AnimationComponent.h"

class Goal
{
public:
	Goal(ResourceManager * resourceManager);
	~Goal();
	void update(const float dt);
	void render(SDL_Renderer * renderer, Camera * cam);
	SDL_Rect getCollisionRect();
	void setCollisionRect(SDL_Rect rect);
	void setCollisionRect(int x, int y, int w, int h);
	bool checkCollision();
	void setPosition(float x, float y);
private:
	SDL_Rect m_collisionRect;
	SDL_Rect m_srcRect;
	SDL_Rect m_destRect;
	SDL_Texture * m_texture;
	int m_currentFrame;
	const int TOTAL_FRAMES;
	const int FRAME_SIDE_LENGTH;
	const float TIME_PER_FRAME;
	float m_timeSinceLastFrame;
};

#endif // !GOAL_H
