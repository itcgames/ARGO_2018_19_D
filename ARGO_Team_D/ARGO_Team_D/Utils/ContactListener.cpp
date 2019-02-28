#include "ContactListener.h"
#include "CollisionData.h"
#include "TutorialTrigger.h"

/// <summary>
/// Function triggers whenever two bodies collide
/// </summary>
/// <param name="contact">Pointer to the contact event</param>
void BodyContactListener::BeginContact(b2Contact* contact)
{
	auto dataA = static_cast<CollisionData*>(contact->GetFixtureA()->GetUserData());
	auto dataB = static_cast<CollisionData*>(contact->GetFixtureB()->GetUserData());

	// Check if fixture A was a body
	if (dataA ) {
		void* bodyUserData = dataA->data;
		if (dataA->tag.find("Body") != std::string::npos)
		{
			if (bodyUserData)
			{
				auto data = static_cast<BodyComponent*>(bodyUserData);
				if (dataA->tag == "BodyGround")
				{
					data->groundContactStart();
				}
				else if (dataA->tag == "BodyLeft")
				{
					data->leftContactStart();
				}
				else if (dataA->tag == "BodyRight")
				{
					data->rightContactStart();
				}
				else if (dataA->tag == "BodyAiRight")
				{
					data->m_AiContact = true;
				}
				else if (dataA->tag == "FlyEnemyBody" && dataB->tag == "PlayerBody")
				{
					auto flyEnemy = static_cast<BodyComponent *>(dataA->data);
					int flyEnemyHitCount = flyEnemy->getBulletHitCount();
					flyEnemy->setBulletHitCount(++flyEnemyHitCount);

					auto player = static_cast<BodyComponent *>(dataB->data);
					int playerHitCount = player->getBulletHitCount();
					player->setBulletHitCount(playerHitCount + 2);
				}
			}
		}
		else if (dataA->tag == "TutorialTrigger") 
		{
			auto data = static_cast<TutorialTrigger*>(bodyUserData);
			data->animateIn();
		}
		else if (dataA->tag.find("Bullet") != std::string::npos)
		{
			auto data = static_cast<Bullet*>(bodyUserData);
			if (dataA->tag == "BulletPlayer" && (dataB->tag == "EnemyBody" || dataB->tag == "FlyEnemyBody"))
			{
				// Enemy is hit by bullet
				auto enemy = static_cast<BodyComponent *>(dataB->data);
				int currentHitCount = enemy->getBulletHitCount();
				enemy->setBulletHitCount(++currentHitCount);
				data->remove();
			}
			else if (dataA->tag == "BulletEnemy" && dataB->tag == "PlayerBody")
			{
				// Player is hit by bullet
				auto player = static_cast<BodyComponent *>(dataB->data);
				int currentHitCount = player->getBulletHitCount();
				player->setBulletHitCount(++currentHitCount);
				data->remove();
			}
			else if (dataB->tag != "PlayerBody" && dataB->tag != "EnemyBody" && dataB->tag != "FlyEnemyBody")
			{
				data->remove();
			}
		}
	}

	// Check if fixture B was a body
	if (dataB) 
	{
		void* bodyUserData = dataB->data;
		if (dataB->tag.find("Body") != std::string::npos)
		{
			if (bodyUserData)
			{
				auto data = static_cast<BodyComponent*>(bodyUserData);
				if (dataB->tag == "BodyGround")
				{
					data->groundContactStart();
				}
				else if (dataB->tag == "BodyLeft")
				{
					data->leftContactStart();
				}
				else if (dataB->tag == "BodyRight")
				{
					data->rightContactStart();
				}
				else if (dataB->tag == "BodyAiRight")
				{
					data->m_AiContact = true;
				}
				else if (dataB->tag == "FlyEnemyBody" && dataA->tag == "PlayerBody")
				{
					auto flyEnemy = static_cast<BodyComponent *>(dataB->data);
					int flyEnemyHitCount = flyEnemy->getBulletHitCount();
					flyEnemy->setBulletHitCount(++flyEnemyHitCount);

					auto player = static_cast<BodyComponent *>(dataA->data);
					int playerHitCount = player->getBulletHitCount();
					player->setBulletHitCount(playerHitCount + 2);
				}
			}
		}
		else if (dataB->tag == "TutorialTrigger") 
		{
			auto data = static_cast<TutorialTrigger*>(bodyUserData);
			data->animateIn();
		}
		else if (dataB->tag.find("Bullet") != std::string::npos)
		{
			auto data = static_cast<Bullet*>(bodyUserData);
			if(dataB->tag == "BulletPlayer" && (dataA->tag == "EnemyBody" || dataA->tag == "FlyEnemyBody"))
			{
				// Enemy is hit by bullet
				auto enemy = static_cast<BodyComponent *>(dataA->data);
				int currentHitCount = enemy->getBulletHitCount();
				enemy->setBulletHitCount(++currentHitCount);
				data->remove();
			}
			else if (dataB->tag == "BulletEnemy" && dataA->tag == "PlayerBody")
			{
				// Player is hit by bullet
				auto player = static_cast<BodyComponent *>(dataA->data);
				int currentHitCount = player->getBulletHitCount();
				player->setBulletHitCount(++currentHitCount);
				data->remove();
			}
			else if (dataA->tag != "PlayerBody" && dataA->tag != "EnemyBody" && dataA->tag != "FlyEnemyBody")
			{
				data->remove();
			}
		}
	}
}

/// <summary>
/// Function triggers whenever two bodies separate
/// </summary>
/// <param name="contact">Pointer to the contact event</param>
void BodyContactListener::EndContact(b2Contact* contact)
{
	auto dataA = static_cast<CollisionData*>(contact->GetFixtureA()->GetUserData());
	auto dataB = static_cast<CollisionData*>(contact->GetFixtureB()->GetUserData());

	// Check if fixture A was a body
	if (dataA) {

		void* bodyUserData = dataA->data;
		if (dataA->tag.find("Body") != std::string::npos)
		{
			if (bodyUserData)
			{
				auto data = static_cast<BodyComponent*>(bodyUserData);
				if (dataA->tag == "BodyGround")
				{
					data->groundContactEnd();
				}
				else if (dataA->tag == "BodyLeft")
				{
					data->leftContactEnd();
				}
				else if (dataA->tag == "BodyRight")
				{
					data->rightContactEnd();
				}
				else if (dataA->tag == "BodyAiRight")
				{
					data->m_AiContact = false;
				}
			}
		}
		else if (dataA->tag == "TutorialTrigger") {
			auto data = static_cast<TutorialTrigger*>(bodyUserData);
			data->animateOut();
		}
	}

	// Check if fixture B was a body
	if (dataB) {
		void* bodyUserData = dataB->data;
		if (dataB->tag.find("Body") != std::string::npos)
		{
			if (bodyUserData)
			{
				auto data = static_cast<BodyComponent*>(bodyUserData);
				if (dataB->tag == "BodyGround")
				{
					data->groundContactEnd();
				}
				else if (dataB->tag == "BodyLeft")
				{
					data->leftContactEnd();
				}
				else if (dataB->tag == "BodyRight")
				{
					data->rightContactEnd();
				}
				else if (dataB->tag == "BodyAiRight")
				{
					data->m_AiContact = false;
				}
			}
		}
		else if (dataB->tag == "TutorialTrigger") {
			auto data = static_cast<TutorialTrigger*>(bodyUserData);
			data->animateOut();
		}
	}
}