#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "Components.h"

/// <summary>
/// Position Component.
/// </summary>
class PositionComponent : public Component {
public:
	PositionComponent(const VectorAPI & v) : m_position(v) { id = "Position"; };
	PositionComponent(float _x, float _y) : m_position(VectorAPI(_x, _y)) { id = "Position"; };
	VectorAPI getPosition() { return m_position; };
	void setPosition(VectorAPI pos);
	void setX(float x);
	void setY(float y);
private:
	VectorAPI m_position;
};

#endif //!POSITIONCOMPONENT_H