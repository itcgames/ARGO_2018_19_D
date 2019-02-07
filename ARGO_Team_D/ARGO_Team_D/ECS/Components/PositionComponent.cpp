#include "PositionComponent.h"

void PositionComponent::setPosition(VectorAPI pos)
{
	m_position = pos;
}

void PositionComponent::setX(float x)
{
	m_position.x = x;
}

void PositionComponent::setY(float y)
{
	m_position.y = y;
}
