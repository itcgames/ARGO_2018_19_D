#include "ContactListener.h"

/// <summary>
/// Function triggers whenever two bodies collide
/// </summary>
/// <param name="contact">Pointer to the contact event</param>
void BodyContactListener::BeginContact(b2Contact* contact)
{
	// Check if fixture A was a body
	void* bodyUserData = contact->GetFixtureA()->GetUserData();
	if (bodyUserData)
	{
		static_cast<BodyComponent*>(bodyUserData)->groundContactStart();
	}

	// Check if fixture B was a body
	bodyUserData = contact->GetFixtureB()->GetUserData();
	if (bodyUserData)
	{
		static_cast<BodyComponent*>(bodyUserData)->groundContactStart();
	}
}

/// <summary>
/// Function triggers whenever two bodies separate
/// </summary>
/// <param name="contact">Pointer to the contact event</param>
void BodyContactListener::EndContact(b2Contact* contact)
{
	// Check if fixture A was a body
	void* bodyUserData = contact->GetFixtureA()->GetUserData();
	if (bodyUserData)
	{
		static_cast<BodyComponent*>(bodyUserData)->groundContactEnd();
	}

	// Check if fixture B was a body
	bodyUserData = contact->GetFixtureB()->GetUserData();
	if (bodyUserData)
	{
		static_cast<BodyComponent*>(bodyUserData)->groundContactEnd();
	}
}