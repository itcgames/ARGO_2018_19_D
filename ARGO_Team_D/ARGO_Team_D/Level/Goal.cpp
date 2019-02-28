#include "Goal.h"

Goal::Goal(ResourceManager * resourceManager)
	: m_currentFrame(0),
	TOTAL_FRAMES(16),
	FRAME_SIDE_LENGTH(200),
	TIME_PER_FRAME(1.f / 30.f),
	m_timeSinceLastFrame(0.f)
{
	m_texture = resourceManager->getImageResource("Portal");
	m_destRect.x = 0;
	m_destRect.y = 0;
	m_destRect.w = FRAME_SIDE_LENGTH;
	m_destRect.h = FRAME_SIDE_LENGTH;
}

Goal::~Goal()
{
}

void Goal::update(const float dt)
{
	m_timeSinceLastFrame += dt;
	if (m_timeSinceLastFrame > TIME_PER_FRAME)
	{
		m_timeSinceLastFrame = 0.f;
		++m_currentFrame;
		if (m_currentFrame >= TOTAL_FRAMES)
		{
			m_currentFrame = 0;
		}
	}
}

void Goal::render(SDL_Renderer * renderer, Camera * cam)
{
	m_srcRect.x = m_currentFrame * FRAME_SIDE_LENGTH;
	m_srcRect.y = 0;
	m_srcRect.w = FRAME_SIDE_LENGTH;
	m_srcRect.h = FRAME_SIDE_LENGTH;
	auto bounds = cam->getBounds();
	m_destRect.x -= bounds.x;
	m_destRect.y -= bounds.y;
	SDL_RenderCopyEx(renderer, m_texture, &m_srcRect, &m_destRect, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE);
	m_destRect.x += bounds.x;
	m_destRect.y += bounds.y;
}

SDL_Rect Goal::getCollisionRect()
{
	return m_collisionRect;
}

void Goal::setCollisionRect(SDL_Rect rect)
{
	m_collisionRect = rect;
}

void Goal::setCollisionRect(int x, int y, int w, int h)
{
	m_collisionRect.x = x;
	m_collisionRect.y = y;
	m_collisionRect.w = w;
	m_collisionRect.h = h;
}

bool Goal::checkCollision()
{
	return false; // TBI
}

void Goal::setPosition(float x, float y)
{
	m_destRect.x = x;
	m_destRect.y = y;
}
