#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "Factory.h"

class EnemyFactory : public Factory
{
public:
	// Public Functions
	EnemyFactory(ResourceManager * rm, b2World & world, const float SCALE, SDL_Renderer * rend);
	~EnemyFactory();
	Enemy * createGunEnemy() override;
	Enemy * createFlyEnemy() override;
	Enemy * createBigEnemy() override;
	Entity * create(std::string spriteId, VectorAPI dimensions, VectorAPI pos) override { return nullptr; };
	Entity * createOnlinePlayer(std::string spriteId, VectorAPI dimensions, VectorAPI pos) override { return nullptr; };
private:
	// Private Functions
	Enemy * createEnemy(string spriteId, int idleFrames, int walkingFrames, int width, int height, bool flying);
};

#endif // !ENEMYFACTORY_H