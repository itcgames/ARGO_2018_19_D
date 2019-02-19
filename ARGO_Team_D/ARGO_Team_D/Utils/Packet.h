#ifndef PACKET_H
#define PACKET_H

#include <string>
#include "VectorAPI.h"

struct Packet {
	int playerID;
	std::string message;
};

#endif //!PACKET_H