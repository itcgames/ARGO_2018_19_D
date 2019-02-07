#ifndef CHARACTERFACTORY_H
#define CHARACTERFACTORY_H

#include "Factory.h"

class CharacterFactory : public Factory {
public:
	CharacterFactory(ResourceManager* rm) { m_resourceManager = rm;  }
	Entity * CreateEntityPlayer(std::string imageId, int entityId, VectorAPI pos, int width, int height);


private:
	ResourceManager * m_resourceManager;
};

#endif
