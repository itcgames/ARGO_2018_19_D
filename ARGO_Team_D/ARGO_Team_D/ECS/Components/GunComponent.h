#ifndef GUNCOMPONENT_H
#define GUNCOMPONENT_H
#include"Components.h"

enum Gun
{
	MACHINE_GUN,
	SHOTGUN,
	GATLING_GUN
};

class GunComponent : public Component 
{
public:
	GunComponent(int gun) { id = "Gun"; m_gun = Gun(gun); };
	int getGun() { return m_gun; };
	void setGun(int gun) { m_gun = Gun(gun); };
private:
	Gun m_gun;
};

#endif // !GUNCOMPONENT_H

