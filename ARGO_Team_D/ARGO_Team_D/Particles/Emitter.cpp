#include "Emitter.h"

Emitter::Emitter(int x, int y, int particleWidth, int particleHeight, SDL_Color color ,SDL_Renderer * renderer , bool isBurst , Uint8 alphaDec)
{
	m_rend = renderer;

	m_posX = x;
	m_posY = y;
	
	width = particleWidth;
	height = particleHeight;
	
	m_color = color;
	emit = true;
	framesPerEmission = 5;
	burst = isBurst;
	looping = false;
	activateBurst = false;
	dir = -1;
	decrement = alphaDec;

	if (!burst)
	{
		/*for (int i = 0; i < 1; i++)
		{
			m_particles.push_back(new Particle(m_posX, m_posY, width, height, m_color, m_rend));
		}*/
	}
	else
	{

	}

	
}

Emitter::~Emitter()
{
	//Delete particles
	for (int i = 0; i < MAX_PARTICLES; ++i)
	{
		delete m_particlesArray[i];
	}

	for (int i = 0; i < m_particles.size(); ++i)
	{
		delete m_particles.at(i);
	}
}

void Emitter::update(int positionX, int positionY)
{
	//std::cout << m_particles.size() << std::endl;
	if (burst)
	{
		if (looping)
		{
			for (int i = 0; i < MAX_PARTICLES; ++i)
			{
				if (m_particlesArray[i] != nullptr)
				{
					if (m_particlesArray[i]->isDead())
					{
						delete m_particlesArray[i];

						m_particlesArray[i] = new Particle(burstX, burstY, width, height, m_color, m_rend, dir, burst, decrement);
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < m_particles.size(); ++i)
		{
			if (m_particles[i]->isDead())
			{
				delete m_particles.at(i);
				//std::cout << m_particles.size() << std::endl;
				m_particles.erase(std::remove(m_particles.begin(), m_particles.end(), m_particles.at(i)), m_particles.end());
			}
		}
	}

	m_posX = positionX;
	m_posY = positionY;

	if (burst && activateBurst)
	{
		for (int i = 0; i < MAX_PARTICLES; i++)
		{
			m_particlesArray[i]->update();
		}
	}
	else
	{
		for (int i = 0; i < m_particles.size(); i++)
		{
			m_particles.at(i)->update();
		}

		if (emit && !burst)
		{

			counter++;
			if (counter % framesPerEmission == 0)
			{
				m_particles.push_back(new Particle(m_posX, m_posY, width, height, m_color, m_rend, dir, burst ,decrement));
				counter = 0;
			}
		}
	}	
}

void Emitter::draw()
{
	drawParticles();
}

void Emitter::setEmitting(bool b)
{
	emit = b;
}

void Emitter::setFramesPerEmission(int num)
{
	framesPerEmission = num;
}

void Emitter::setLooping(bool b)
{
	looping = b;
}

void Emitter::setDirection(int num)
{
	dir = num;
}

int Emitter::getDirection()
{
	return dir;
}

void Emitter::activate(bool b)
{
	activateBurst = true;
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		m_particlesArray[i] = (new Particle(m_posX, m_posY, width, height, m_color, m_rend, dir, burst, decrement));
	}
}

void Emitter::activate(bool b, int x, int y)
{
	activateBurst = true;
	burstX = x;
	burstY = y;
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		m_particlesArray[i] = (new Particle(burstX, burstY, width, height, m_color, m_rend, dir, burst, decrement));
	}
}

void Emitter::setAlphaDec(int num)
{
}

void Emitter::drawParticles()
{
	if (burst)
	{
		if (looping)
		{
			for (int i = 0; i < MAX_PARTICLES; ++i)
			{
				/*if (m_particlesArray[i] != nullptr)
				{
					if (m_particlesArray[i]->isDead())
					{
						delete m_particlesArray[i];
						m_particlesArray[i] = new Particle(m_posX, m_posY, width, height, m_color, m_rend, dir, burst, decrement);
					}
				}*/
			}
		}
		

		for (int i = 0; i < MAX_PARTICLES; ++i)
		{
			if (activateBurst)
			{
				m_particlesArray[i]->draw();
			}		
		}
	}
	else
	{
		/*for (int i = 0; i < m_particles.size(); ++i)
		{
			if (m_particles[i]->isDead())
			{
				delete m_particles.at(i);
				m_particles.erase(std::remove(m_particles.begin(), m_particles.end(), m_particles.at(i)), m_particles.end());
			}
		}*/
		//std::cout << m_particles.size() << std::endl;
		//Show particles
		for (int i = 0; i < m_particles.size(); ++i)
		{
			m_particles.at(i)->draw();
		}
	}
}
