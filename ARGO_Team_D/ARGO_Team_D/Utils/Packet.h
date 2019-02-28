#ifndef PACKET_H
#define PACKET_H

#include <string>
#include "VectorAPI.h"

enum MessageType {
	NONE,
	HOSTING,
	JOINED,
	POSITION,
	PLAYER,
	START,
	ALLREADY,
	READY,
	UNREADY,
	LOBBYCREATED,
	LOBBYUPDATED,
	LEAVELOBBY,
	JOINLOBBY,
	LOBBYINFO
};

struct Packet {
	int playerID;
	MessageType type;
	VectorAPI position;
	int numOtherPlayers;
};

#endif //!PACKET_H