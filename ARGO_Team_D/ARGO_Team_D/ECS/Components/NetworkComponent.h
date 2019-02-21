#ifndef NETWORKCOMPONENT_H
#define NETWORKCOMPONENT_H

#include "Components.h"

class NetworkComponent : public Component
{
public:
	NetworkComponent(int netID) : networkID(netID) { id = "Network"; }
	int networkID;
};
#endif // !NETWORKCOMPONENT_H