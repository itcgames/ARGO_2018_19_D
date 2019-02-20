#ifndef NETWORKCOMPONENT_H
#define NETWORKCOMPONENT_H

#include "Components.h"

class NetworkComponent : public Component
{
public:
	NetworkComponent(int netID);
	int getID();
private:
	// Private Members
	int networkID;
};

#endif // !NETWORKCOMPONENT_H
