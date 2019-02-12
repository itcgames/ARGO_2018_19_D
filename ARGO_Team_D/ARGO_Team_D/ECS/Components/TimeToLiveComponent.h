#ifndef TIMETOLIVECOMPONENT_H
#define TIMETOLIVECOMPONENT_H

#include"Components.h"
#include<SDL.h>
class TimeToLiveComponent: public Component 
{
public:
	TimeToLiveComponent(float ttl = 0) { id = "TimeToLive"; m_ttl = ttl; }
	float getTTL() { return m_ttl; }
	float getStart() { return m_start; }
	void setTimer(float time) { m_start = time; }
	void setActive(bool b) { m_active = b; }
	bool isActive() { return m_active; }
private:
	float m_ttl;
	float m_start = SDL_GetTicks();
	bool m_active = false;
};

#endif // !TIMETOLIVECOMPONENT_H

