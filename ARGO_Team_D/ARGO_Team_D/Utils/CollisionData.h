#ifndef COLLISIONDATA_H
#define COLLISIONDATA_H

#include <string>

struct CollisionData {
	enum _entityCategory {
		PLAYER = 0x0001,
		TUTORIAL = 0x0002,
		GROUNDSENSOR = 0x0004,
		GROUND = 0x0008,
		BULLET = 0x0010,
		ENEMY = 0x0020
	};

	CollisionData(std::string type, void * userdata) :
		tag(type),
		data(userdata) {

	};
	std::string tag;
	void * data;
};

#endif //!COLLISIONDATA_H