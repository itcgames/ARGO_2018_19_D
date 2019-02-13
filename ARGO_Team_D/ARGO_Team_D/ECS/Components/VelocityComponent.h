#ifndef VELOCITYCOMPONENT_H
#define VELOCITYCOMPONENT_H
#include "Components.h"
#include "../Utils/VectorAPI.h"
class VelocityComponent : public Component
{
public:
	VelocityComponent(VectorAPI velocity) { id = "Velocity"; m_velocity = velocity; }
	VectorAPI getVelocity() { return m_velocity; };
	void setVelocity(VectorAPI v) { m_velocity = v; }
private:
	VectorAPI m_velocity;
};

#endif // !VELOCITYCOMPONENT_H
