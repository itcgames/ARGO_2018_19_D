#ifndef CONTACTLISTENER
#define CONTACTLISTENER

#include <Box2D/Box2D.h>
#include "../ECS/Components/BodyComponent.h"
#include "../Bullets/Bullet.h"

/// <summary>
/// Contact Listener for Box2D bodies, main purpose is to check for grounding
/// </summary>
class BodyContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};

#endif // !CONTACTLISTENER
