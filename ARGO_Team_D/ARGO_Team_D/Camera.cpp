#include "Camera.h"
#include "Utils/MathUtils.h"
#include <cmath>
#include <iostream>

Camera::Camera(const int windowWidth, const int windowHeight) :
	m_scale(1,1),
	m_bounds({ 0,0, windowWidth, windowHeight }),
	m_originalSize(windowWidth, windowHeight)
{
	m_viewOffset = 0;
	m_weight = 0.1f;
	m_maxOffset = 3;
	m_shake = 1.0;
}

void Camera::update(const VectorAPI & boundPosition, const float & rotation)
{
	VectorAPI boundPos = boundPosition;
	
	float rotInRadians = mu::degToRadians(rotation);
	boundPos.x += std::cos(rotInRadians) * m_viewOffset;
	boundPos.y += std::sin(rotInRadians) * m_viewOffset;

	m_position.x += ((boundPos.x - m_position.x) * m_weight);
	m_position.y += ((boundPos.y - m_position.y) * m_weight);

	if (m_shaking) {
		float min = -1;
		float max = 1;
		auto val = min + ((float)rand() / (float)RAND_MAX) * (max - min);
		m_offset.x = m_maxOffset * m_shake * val;
		m_offset.y = m_maxOffset * m_shake * val;
		m_position += m_offset;
	}

	m_bounds.x = m_position.x - (m_bounds.w / 2);
	m_bounds.y = m_position.y - (m_bounds.h / 2);
}

void Camera::setPosition(const VectorAPI & position)
{
	m_position = position;
}

void Camera::setSize(const VectorAPI & size)
{
	m_bounds.w = size.x;
	m_bounds.y = size.y;
}

void Camera::setBounds(const SDL_Rect & bounds)
{
	m_bounds = bounds;
}

void Camera::setScale(const VectorAPI & scale)
{
	m_scale = scale;
	m_bounds.x /= m_scale.x;
	m_bounds.y /= m_scale.y;
	m_bounds.w = m_originalSize.x / m_scale.x;
	m_bounds.h = m_originalSize.y / m_scale.y;
	std::cout << m_scale.x << ", " << m_scale.y << std::endl;
}

VectorAPI Camera::getOriginalSize()
{
	return m_originalSize;
}

SDL_Rect Camera::getBounds()
{
	return m_bounds;
}
