#include "Camera.h"
#include "Utils/MathUtils.h"
#include <cmath>
#include <iostream>

Camera::Camera()
{
	m_viewOffset = 0;
	m_weight = 1;
}

void Camera::update(const SdlVector & boundPosition, const float & rotation)
{
	SdlVector boundPos = boundPosition;
	
	float rotInRadians = mu::degToRadians(rotation);
	boundPos.x += std::cos(rotInRadians) * m_viewOffset;
	boundPos.y += std::sin(rotInRadians) * m_viewOffset;

	m_position.x += ((boundPos.x - m_position.x) * m_weight);
	m_position.y += ((boundPos.y - m_position.y) * m_weight);

	m_bounds.x = m_position.x - (m_bounds.w / 2);
	m_bounds.y = m_position.y - (m_bounds.h / 2);
	std::cout << "x:" << m_bounds.x << ", y: " << m_bounds.y << std::endl;
}

void Camera::setPosition(const SdlVector & position)
{
	m_position = position;
}

void Camera::setSize(const SdlVector & size)
{
	m_bounds.w = size.x;
	m_bounds.y = size.y;
}

void Camera::setBounds(const SDL_Rect & bounds)
{
	m_bounds = bounds;
}

SDL_Rect Camera::getBounds()
{
	return m_bounds;
}
