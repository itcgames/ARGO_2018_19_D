#ifndef EMITTER_H
#define EMITTER_H

#include<SDL.h>
#include<SDL_image.h>
#include"Particle.h"
#include<vector>
#include<algorithm>


const int MAX_PARTICLES = 50;

class Emitter
{
public:

	Emitter(int x, int y, int particleWidth, int particleHeight, SDL_Color color, SDL_Renderer * renderer, bool isBurst, Uint8 alphaDec);
	~Emitter();

	void update(int positionX, int positionY);
	void draw();
	void setEmitting(bool b);
	void setFramesPerEmission(int num);
	void setLooping(bool b);
	void setDirection(int num);
	int getDirection();
	void activate(bool b);

	void setAlphaDec(int num);
private:
	//Particle* m_particles[MAX_PARTICLES];
	std::vector<Particle *> m_particles;
	Particle* m_particlesArray[MAX_PARTICLES];
	void drawParticles();
	int m_posX, m_posY;
	SDL_Renderer * m_rend;

	int width, height;

	int counter;

	SDL_Color m_color;

	bool emit;

	int framesPerEmission; // the number of frames that pass before a particle is emitted

	bool burst;

	bool looping;

	int dir;

	bool activateBurst;

	Uint8 decrement;
};

#endif // !EMITTER_H

