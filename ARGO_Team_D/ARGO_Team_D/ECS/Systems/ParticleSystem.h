#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include"System.h"
#include<SDL.h>
#include"../Components/ParticleEffectsComponent.h"
#include"../Components/BodyComponent.h"
#include"../Camera.h"

struct ParticleComponents
{
	ParticleEffectsComponent * part;
	BodyComponent * body;
};

class ParticleSystem: public System 
{
public:
	ParticleSystem(Camera * cam);
	~ParticleSystem();
	void update();
	void draw();
	void addEntity(Entity * e) override;
private:
	std::vector<std::string> allowedTypes;
	std::vector<ParticleComponents> m_components;
	Camera * m_cam;
	const float WORLD_SCALE = 30.f;
	int num;
};

#endif // !PARTICLESYSTEM_H

