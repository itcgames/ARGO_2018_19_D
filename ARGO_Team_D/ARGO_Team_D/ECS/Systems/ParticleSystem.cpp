#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Camera & cam)
{
	this->cam = &cam;
	allowedTypes.push_back("Particle");
	allowedTypes.push_back("Body");
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::update()
{
	for (auto & pc : m_components)
	{
		pc.part->m_emitter.update((pc.body->getBody()->GetPosition().x * WORLD_SCALE) - (pc.body->getDimensions().x / 2  * pc.part->m_emitter.getDirection())- cam->getBounds().x,
			(pc.body->getBody()->GetPosition().y * WORLD_SCALE) + pc.body->getDimensions().y / 2 - cam->getBounds().y);

		pc.part->m_emitterExplos.update((pc.body->getBody()->GetPosition().x * WORLD_SCALE) - cam->getBounds().x,
			(pc.body->getBody()->GetPosition().y * WORLD_SCALE) - cam->getBounds().y);

		if ((pc.body->getBody()->GetLinearVelocity().x > 0 || pc.body->getBody()->GetLinearVelocity().x < 0) && pc.body->getBody()->GetLinearVelocity().y == 0 )
		{
			pc.part->m_emitter.setEmitting(true);
		}
		else
		{
			pc.part->m_emitter.setEmitting(false);
		}
		
	}
}

void ParticleSystem::draw()
{
	for (auto & pc : m_components)
	{
		pc.part->m_emitter.draw();
		pc.part->m_emitterExplos.draw();
	}
}

void ParticleSystem::addEntity(Entity * e)
{
	num++;
	std::cout << "Entitys: " << num << std::endl;
	std::vector<std::string> allowedTypes{ "Particle", "Body" };
	auto comps = e->getComponentsOfType(allowedTypes);
	if (comps.size() == allowedTypes.size())
	{
		ParticleComponents c;
		c.part = dynamic_cast<ParticleEffectsComponent*>(comps["Particle"]);
		c.body = dynamic_cast<BodyComponent*>(comps["Body"]);
		m_components.push_back(c);
		m_entityList.push_back(e);
	}
}
