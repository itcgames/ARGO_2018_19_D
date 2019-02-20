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
	START
};

struct Packet {
	int playerID;
	MessageType type;
	VectorAPI position;
};

#endif //!PACKET_H