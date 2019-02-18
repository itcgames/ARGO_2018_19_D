#include "ControlSystem.h"

ControlSystem::ControlSystem()
{
	allowedTypes = { "Body", "Position", "Gun" };
	direction = 1;
}

ControlSystem::~ControlSystem()
{
}

void ControlSystem::addEntity(Entity * e)
{
	std::vector<std::string> allowedTypes{ "Body" , "Animation"};
	auto comps = e->getComponentsOfType(allowedTypes);
	if (comps.size() >= allowedTypes.size() - 1)
	{
		ControlComponents c;
		c.body = dynamic_cast<BodyComponent*>(comps["Body"]); 
		c.animation = dynamic_cast<AnimationComponent*>(comps["Animation"]);
		m_components.insert(std::make_pair(e->id, c));
		m_entityList.push_back(e);
	}
}

void ControlSystem::update()
{
	for (auto & comp : m_components)
	{
		auto & cc = comp.second;
		BodyComponent * body = cc.body;
		if (body != nullptr)
		{
			b2Body * b2Body = body->getBody();
			b2Vec2 currentVelocity = b2Body->GetLinearVelocity();
			if (m_jump)
			{
				b2Body->SetLinearVelocity(b2Vec2(currentVelocity.x, -35));
				currentVelocity.y = -35;
			}
			if (m_moveRight)
			{
				b2Body->SetLinearVelocity(b2Vec2(15, currentVelocity.y));
				currentVelocity.x = 15;
			}
			else if (m_moveLeft)
			{
				b2Body->SetLinearVelocity(b2Vec2(-15, currentVelocity.y));
				currentVelocity.x = -15;
			}
			else
			{
				b2Body->SetLinearVelocity(b2Vec2(0, currentVelocity.y));
				currentVelocity.x = 0;
			}

			if (m_fire)
			{
				spawnProjectile(b2Body->GetPosition().x * 30.0f, b2Body->GetPosition().y * 30.0f);
			}
			m_moveRight = false, m_moveLeft = false, m_jump = false, m_fire = false;
		}
	}

}

void ControlSystem::moveRight()
{
	m_moveRight = true;
	direction = 1;
}

void ControlSystem::moveLeft()
{
	m_moveLeft = true;
	direction = -1;
}

void ControlSystem::jump()
{
	m_jump = true;
}

void ControlSystem::fire()
{
	m_fire = true;	
}

void ControlSystem::bindBullets(std::vector<Entity*>& bullets)
{
	m_bullets = bullets;
}

void ControlSystem::spawnProjectile(float x, float y)
{

	for (auto &e : m_entityList)
	{
		std::vector<std::string> s = { "Gun" };
		auto comps = e->getComponentsOfType(s);
		GunComponent * g = dynamic_cast<GunComponent*>(comps["Gun"]);

		if (g != nullptr)
		{
			switch (Gun(g->getGun()))
			{
			case MACHINE_GUN:
				for (auto &b : m_bullets)
				{

					std::vector<std::string> s = { "TimeToLive", "Position", "Velocity" };
					auto comps = b->getComponentsOfType(s);
					TimeToLiveComponent * t = dynamic_cast<TimeToLiveComponent*>(comps["TimeToLive"]);

					if (!t->isActive())
					{
						t->setActive(true);
						PositionComponent * p = dynamic_cast<PositionComponent*>(comps["Position"]);
						p->setPosition(VectorAPI(x, y));

						VelocityComponent * v = dynamic_cast<VelocityComponent*>(comps["Velocity"]);
						v->setVelocity(VectorAPI(25 * direction, ((double)rand() / RAND_MAX) * 2 - 1));
						t->setTimer(SDL_GetTicks());
						t->setActive(true);
						break;
					}
				}
				break;
			case SHOTGUN:
				for (auto &b : m_bullets)
				{
					if (counter < 5)
					{
						std::vector<std::string> s = { "TimeToLive", "Position", "Velocity" };
						auto comps = b->getComponentsOfType(s);
						TimeToLiveComponent * t = dynamic_cast<TimeToLiveComponent*>(comps["TimeToLive"]);

						if (!t->isActive())
						{
							t->setActive(true);
							PositionComponent * p = dynamic_cast<PositionComponent*>(comps["Position"]);
							p->setPosition(VectorAPI(x, y));

							VelocityComponent * v = dynamic_cast<VelocityComponent*>(comps["Velocity"]);
							if (counter % 2 == 0)
							{
								//v->setVelocity(VectorAPI(20 * direction, counter * 5.f));
								auto vec = VectorAPI(direction, counter * 0.015f).Normalize() * 20.f;
								v->setVelocity(vec);
							}
							else
							{
								auto vec = VectorAPI(direction, counter * -0.015f).Normalize() * 20.f;
								v->setVelocity(vec);
							}

							t->setTimer(SDL_GetTicks());
							t->setActive(true);
						}
					}
					else
					{
						counter = 0;
						break;
					}
					counter++;
				}
				break;
			}
		}
		
	
	}
	
}

void ControlSystem::removeEntity(const int id)
{
	auto comp = m_components.find(id);
	if (comp != m_components.end()) {
		m_components.erase(comp);
	}
	m_entityList.erase(std::remove_if(m_entityList.begin(), m_entityList.end(), [id](Entity* en) {
		return en->id == id;
	}), m_entityList.end());
}

void ControlSystem::processInput(SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN) {
		std::vector<string> allowedTypes = {"Body", "Animation" };
		for (auto & comp : m_components)
		{
			auto & cc = comp.second;
			if (cc.animation)
				cc.animation->handleInput(event);
		}
	}
}
