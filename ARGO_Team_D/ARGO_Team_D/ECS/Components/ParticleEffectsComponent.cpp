#include "ParticleEffectsComponent.h"

ParticleEffectsComponent::ParticleEffectsComponent(int x, int y, int particleWidth, int particleHeight, SDL_Color trailColor, SDL_Color burstColor, SDL_Renderer * renderer, bool isBurst, Uint8 alphaDec) : m_emitter(x, y, particleWidth, particleHeight, trailColor, renderer, isBurst, alphaDec), m_emitterExplos(x, y, particleWidth * 2, particleHeight * 2, burstColor, renderer, true, 10)
{
	id = "Particle";
	emit = true;
}

//void ParticleEffectsComponent::setEmitting(bool b)
//{
//	m_emitter.setEmitting(b);
//}
//
//void ParticleEffectsComponent::setFramesPerEmission(int num)
//{
//	m_emitter.setFramesPerEmission(num);
//}
//
//void ParticleEffectsComponent::setLooping(bool b)
//{
//	m_emitter.setLooping(b);
//}
//
//void ParticleEffectsComponent::setDir(int num)
//{
//	m_emitter.setDirection(num);
//}
