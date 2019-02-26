#include "AiComponent.h"

AiComponent::AiComponent(AiType type, int xMax, int xMin, int hits) 
	: m_type(type), 
	m_active(false), 
	m_direction(1),
	m_xMax(xMax),
	m_xMin(xMin),
	m_hits(hits),
	m_shotTimer(0.f)
{
	id = "Ai";
}

AiComponent::~AiComponent()
{
}

void AiComponent::setMovementMarkers(int min, int max)
{
	m_xMin = min;
	m_xMax = max;
}

void AiComponent::setActivationState(bool state)
{
	m_active = state;
}

bool AiComponent::getActivationState()
{
	return m_active;
}

void AiComponent::setDirection(int direction)
{
	m_direction = direction == -1 ? -1 : 1;
}

int AiComponent::getDirection()
{
	return m_direction;
}

int AiComponent::getMinX()
{
	return m_xMin;
}

int AiComponent::getMaxX()
{
	return m_xMax;
}

int AiComponent::getMaxHits()
{
	return m_hits;
}

AiType AiComponent::getType()
{
	return m_type;
}

void AiComponent::setShotTimer(float val)
{
	m_shotTimer = val;
}

float AiComponent::getShotTimer()
{
	return m_shotTimer;
}
