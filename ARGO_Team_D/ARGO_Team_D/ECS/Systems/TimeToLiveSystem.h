#ifndef TIMETOLIVESYSTEM_H
#define TIMETOLIVESYSTEM_H

#include"System.h"
#include"../Components/TimeToLiveComponent.h"

class TimeToLiveSystem: public System
{
public:
	TimeToLiveSystem();
	void update();
private:
	std::vector<std::string> m_allowedTypes;
};


#endif // !TIMETOLIVESYSTEM_H