#include "NetworkComponent.h"

NetworkComponent::NetworkComponent(int netID)
	: networkID(netID)
{
}

int NetworkComponent::getID()
{
	return networkID;
}
