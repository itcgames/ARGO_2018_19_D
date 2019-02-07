#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "Components.h"

/// <summary>
/// Position Component.
/// </summary>
class PositionComponent : public Component {
public:
	PositionComponent(const SdlVector & v) : m_position(v) { id = "Position"; };
	PositionComponent(float _x, float _y) : m_position(SdlVector(_x, _y)) { id = "Position"; };
	SdlVector getPosition() { return m_position; };
	SdlVector m_position;
private:
};

#endif //!POSITIONCOMPONENT_H