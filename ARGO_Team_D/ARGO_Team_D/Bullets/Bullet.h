#ifndef BULLET_H
#define BULLET_H

#include <Box2D/Box2D.h>
#include "../Utils/VectorAPI.h"
#include "../Utils/CollisionData.h"
#include "../Resource Manager/ResourceManager.h"
#include "../Camera.h"

class Bullet
{
public:
	Bullet(b2World & world, const float SCALE, ResourceManager * resourceManager, VectorAPI posIn, float speedIn, bool isPlayer);
	~Bullet();
	void update(float dt);
	void draw(SDL_Renderer * renderer, Camera & camera);
	void collide();
	bool isActive();
	void remove();
private:
	b2World & m_refWorld;
	const float WORLD_SCALE;

	// Box2D Body
	b2Body * m_body;
	b2BodyDef m_bodyDef;
	b2Shape * m_shape;
	b2FixtureDef m_fixtureDef;
	CollisionData collisionData;

	// Drawables
	ResourceManager * m_resourceManager;
	SDL_Texture * m_texture;
	SDL_Rect m_dest;

	// Attributes
	bool m_isActive;
	float m_speed;
	float m_ttl;
	VectorAPI m_dimensions;
};

#endif // !BULLET_H

