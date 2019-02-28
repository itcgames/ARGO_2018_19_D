#ifndef PARTICLEEFFECTSCOMPONENT_H
#define PARTICLEEFFECTSCOMPONENT_H

#include"Components.h"
#include"../Particles/Emitter.h"

class ParticleEffectsComponent: public Component {

public:
	ParticleEffectsComponent(int x, int y, int particleWidth,
		int particleHeight, SDL_Color trailColor, SDL_Color burstColor, SDL_Renderer * renderer,
		bool isBurst, Uint8 alphaDec);
	Emitter m_emitter;
	Emitter m_emitterExplos;
	bool emit;
	/*void setEmitting(bool b);
	void setFramesPerEmission(int num);
	void setLooping(bool b);
	void setDir(int num);*/
private:
	
};

#endif // !PARTICLEEFFECTSCOMPONENT_H

