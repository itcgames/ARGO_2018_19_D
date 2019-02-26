#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Camera * cam)
{
	m_cam = cam;
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
		pc.part->m_emitter.update((pc.body->getBody()->GetPosition().x * WORLD_SCALE) - (pc.body->getDimensions().x / 2.f  * pc.part->m_emitter.getDirection()),
			(pc.body->getBody()->GetPosition().y * WORLD_SCALE) + pc.body->getDimensions().y / 2.f );

		pc.part->m_emitterExplos.update(0, 0);

		if ( pc.part->emit == true &&((pc.body->getBody()->GetLinearVelocity().x > 0 || pc.body->getBody()->GetLinearVelocity().x < 0) && pc.body->getBody()->GetLinearVelocity().y == 0) )
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
		pc.part->m_emitter.draw(m_cam);
		pc.part->m_emitterExplos.draw(m_cam);
	}
}

void ParticleSystem::addEntity(Entity * e)
{
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
