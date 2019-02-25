#include "BulletManager.h"

BulletManager::BulletManager(b2World & world, float const SCALE, ResourceManager * resourceManager) 
	: m_refWorld(world),
	WORLD_SCALE(SCALE),
	m_resourceManager(resourceManager)
{

}

BulletManager::~BulletManager()
{
	for (auto & bullet : m_bullets)
	{
		delete bullet;
	}
}

void BulletManager::createBullet(VectorAPI posIn, float speedIn, bool isPlayer)
{
	m_bullets.push_back(new Bullet(m_refWorld, WORLD_SCALE, m_resourceManager, posIn, speedIn, isPlayer));
}

void BulletManager::update(float dt)
{
	for (int i = 0; i < m_bullets.size(); )
	{
		if (!m_bullets.at(i)->isActive())
		{
			delete m_bullets.at(i);
			m_bullets.erase(std::remove(m_bullets.begin(), m_bullets.end(), m_bullets.at(i)), m_bullets.end());
		}
		else
		{
			m_bullets.at(i)->update(dt);
			++i;
		}
	}
}

void BulletManager::render(SDL_Renderer * renderer, Camera & camera)
{
	for (auto & bullet : m_bullets)
	{
		bullet->draw(renderer, camera);
	}
}