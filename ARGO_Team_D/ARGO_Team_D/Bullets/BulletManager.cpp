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
	// Test Code
	std::cout << m_bullets.size() << std::endl;
	if (m_bullets.size() == 0)
	{
		createBullet(VectorAPI(-1600, 0), 25, false);
		createBullet(VectorAPI(-1500, 0), 25, false);
		createBullet(VectorAPI(-1400, 0), 25, false);
		createBullet(VectorAPI(-1300, 0), 25, false);
		createBullet(VectorAPI(-1200, 0), 25, false);
		createBullet(VectorAPI(-1100, 0), 25, false);
		createBullet(VectorAPI(-1000, 0), 25, false);
		createBullet(VectorAPI(-900, 0), 25, false);
		createBullet(VectorAPI(-800, 0), 25, false);
		createBullet(VectorAPI(-700, 0), 25, false);
		createBullet(VectorAPI(-600, 0), 25, false);
		createBullet(VectorAPI(-500, 0), 25, false);
		createBullet(VectorAPI(-400, 0), 25, false);
	}
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