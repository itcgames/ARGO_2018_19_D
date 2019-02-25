#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include "Bullet.h"

class BulletManager
{
public:
	BulletManager(b2World & world, const float SCALE, ResourceManager * resourceManager);
	~BulletManager();
	void createBullet(VectorAPI posIn, float speed, bool isPlayer);
	void update(float dt);
	void render(SDL_Renderer * renderer, Camera & camera);
private:
	b2World & m_refWorld;
	const float WORLD_SCALE;
	ResourceManager * m_resourceManager;
	std::vector<Bullet *> m_bullets;
};

#endif // !BULLET_H
