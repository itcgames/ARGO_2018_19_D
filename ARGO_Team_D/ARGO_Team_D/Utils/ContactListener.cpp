#include "ContactListener.h"
#include "../Level/Level.h"

/// <summary>
/// Function triggers whenever two bodies collide
/// </summary>
/// <param name="contact">Pointer to the contact event</param>
void BodyContactListener::BeginContact(b2Contact* contact)
{
	auto dataA = static_cast<CollisionData*>(contact->GetFixtureA()->GetUserData());
	auto dataB = static_cast<CollisionData*>(contact->GetFixtureB()->GetUserData());
	// Check if fixture A was a body
	if (dataA && dataA->tag == "Body") {
		std::cout << "Entry " << dataA->tag << std::endl;
		void* bodyUserData = dataA->data;
		if (bodyUserData)
		{
			auto data = static_cast<BodyComponent*>(bodyUserData);
			data->groundContactStart();
		}
	}
	// Check if fixture B was a body
	if (dataB && dataB->tag == "Body") {
		std::cout << "Entry " << dataB->tag << std::endl;
		void* bodyUserData = dataB->data;
		if (bodyUserData)
		{
			auto data = static_cast<BodyComponent*>(bodyUserData);
			data->groundContactStart();
		}
	}

	if (dataA && dataA->tag == "TutorialTrigger") {
		std::cout << "Tutorial trigger A" << std::endl;
	}
	if (dataB && dataB->tag == "TutorialTrigger") {
		std::cout << "Tutorial trigger B" << std::endl;
	}
}

/// <summary>
/// Function triggers whenever two bodies separate
/// </summary>
/// <param name="contact">Pointer to the contact event</param>
void BodyContactListener::EndContact(b2Contact* contact)
{
	// Check if fixture A was a body
	auto dataA = static_cast<CollisionData*>(contact->GetFixtureA()->GetUserData());
	auto dataB = static_cast<CollisionData*>(contact->GetFixtureB()->GetUserData());
	if (dataA && dataA->tag == "Body") {
		std::cout << "End " << dataA->tag << std::endl;
		void* bodyUserData = dataA->data;
		if (bodyUserData)
		{
			auto data = static_cast<BodyComponent*>(bodyUserData);
			data->groundContactEnd();
		}
	}
	// Check if fixture B was a body
	if (dataB && dataB->tag == "Body") {
		std::cout << "End " << dataB->tag << std::endl;
		void* bodyUserData = dataB->data;
		if (bodyUserData)
		{
			auto data = static_cast<BodyComponent*>(bodyUserData);
			data->groundContactEnd();
		}
	}

	if (dataA && dataA->tag == "TutorialTrigger") {
		std::cout << "Tutorial trigger A" << std::endl;
	}
	if (dataB && dataB->tag == "TutorialTrigger") {
		std::cout << "Tutorial trigger B" << std::endl;
	}
}