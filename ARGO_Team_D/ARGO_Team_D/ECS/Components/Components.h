#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <utility>
#include <string>
#include "../Utils/VectorAPI.h"

/// <summary>
/// Component Interface
/// </summary>
class Component {
public:
	Component() {}
	virtual ~Component() {}
	std::string id;
protected:

};

#endif // !COMPONENTS_H