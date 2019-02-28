#include "Emitter.h"

/// <summary>
/// Emitter constructor function
/// </summary>
/// <param name="x">X position of emitter</param>
/// <param name="y">Y position of emitter</param>
/// <param name="particleWidth">Width of emiiter particles</param>
/// <param name="particleHeight">Height of emiiter particles</param>
/// <param name="color">Color of emitter particles</param>
/// <param name="renderer">Renderer to draw to window</param>
/// <param name="isBurst">Bool to tell whether the particles should be a stream or burst</param>
/// <param name="alphaDec">Alpha decrement to use when fading particles</param>
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
}

/// <summary>
/// Emitter destructor function
/// </summary>
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

/// <summary>
/// Emitter update function
/// </summary>
/// <param name="positionX">X position of emitter</param>
/// <param name="positionY">Y position of emitter</param>
void Emitter::update(int positionX, int positionY)
{
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

/// <summary>
/// Draw function of emitter
/// </summary>
/// <param name="cam">Camera used for drawing</param>
void Emitter::draw(Camera * cam)
{
	drawParticles(cam);
}

/// <summary>
/// Function sets an emitter off to start emitting particles
/// </summary>
/// <param name="b">Bool emission state</param>
void Emitter::setEmitting(bool b)
{
	emit = b;
}

/// <summary>
/// Function sets the frequency of emission in frames
/// </summary>
/// <param name="num">Frames per emission</param>
void Emitter::setFramesPerEmission(int num)
{
	framesPerEmission = num;
}

/// <summary>
/// Function allows the looping state of emitter to be set
/// </summary>
/// <param name="b">Bool desired looping state</param>
void Emitter::setLooping(bool b)
{
	looping = b;
}

/// <summary>
/// Set the direction of the emitter
/// </summary>
/// <param name="num">Int desired direction</param>
void Emitter::setDirection(int num)
{
	dir = num;
}

/// <summary>
/// Get the direction of the emitter
/// </summary>
/// <returns>Int direction</returns>
int Emitter::getDirection()
{
	return dir;
}

/// <summary>
/// Activates a burst emitter
/// </summary>
void Emitter::activate()
{
	activateBurst = true;
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		m_particlesArray[i] = (new Particle(m_posX, m_posY, width, height, m_color, m_rend, dir, burst, decrement));
	}
}

/// <summary>
/// Activates a burst emitter
/// </summary>
/// <param name="x">X position</param>
/// <param name="y">Y position</param>
void Emitter::activate(int x, int y)
{
	activateBurst = true;
	burstX = x;
	burstY = y;
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		m_particlesArray[i] = (new Particle(burstX, burstY, width, height, m_color, m_rend, dir, burst, decrement));
	}
}

/// <summary>
/// Draws all particles
/// </summary>
/// <param name="cam">Camera used for rendering</param>
void Emitter::drawParticles(Camera * cam)
{
	//Show particles
	if (burst)
	{
		for (int i = 0; i < MAX_PARTICLES; ++i)
		{
			if (activateBurst)
			{
				m_particlesArray[i]->draw(cam);
			}		
		}
	}
	else
	{
		for (int i = 0; i < m_particles.size(); ++i)
		{
			m_particles.at(i)->draw(cam);
		}
	}
}
