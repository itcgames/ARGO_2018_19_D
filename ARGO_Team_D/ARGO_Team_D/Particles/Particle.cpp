#include "Particle.h"

/// <summary>
/// Particle constrcutor function, sets up particle paarameters for width and height etc.
/// </summary>
/// <param name="x">X position of the particle</param>
/// <param name="y">Y position of the particle</param>
/// <param name="width">Width of the particle</param>
/// <param name="height">Height of the particle</param>
/// <param name="color">Color of the particle</param>
/// <param name="renderer">Renderer used to draw to screen</param>
/// <param name="dir">int (-1 to 1) to indicate particle direction</param>
/// <param name="isBurst">Bool to inform particle whether it is part of an burst or continuous stream</param>
/// <param name="dec">decrement per frame from the particles color alpha</param>
Particle::Particle(int x, int y, int width, int height, SDL_Color color, SDL_Renderer * renderer, int dir, bool isBurst, Uint8 dec)
{
	m_rend = renderer;
	m_width = width;
	m_height = height;

	if (!isBurst)
	{
		m_posX = x; //+ (rand() % 40 + 1) - 20;
		m_posY = y; //+ (rand() % 40 + 1) - 20;
		float speed = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.5f))) + 0.2f;
		float angle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * acos(-1))));
		m_velX = speed * cos(angle) - (1.5f * dir);
		m_velY = speed * sin(angle) - 2.f;
	}
	else
	{
		m_posX = x + (rand() % 40 + 1) - 20;
		m_posY = y + (rand() % 40 + 1) - 20;
		float speed = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.5f))) + 0.8f;
		float angle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * acos(-1))));
		m_velX = speed * cos(angle);
		m_velY = speed * sin(angle) - 4.f;
		m_velX *= 1.75f;
		m_velY *= 1.75f;
	}
	srcrect = { 0, 0, 10, 10 };
	dstrect = { 0, 0, 10, 10 };

	m_frame = 0;
	alpha = 255;
	this->color = { color.r, color.g, color.b, alpha };
	dead = false;
	decrement = dec;
}
	
/// <summary>
/// Particle destructor
/// </summary>
Particle::~Particle()
{
}

/// <summary>
/// Particle update function, used to move the particle and alter its' alpha value
/// </summary>
void Particle::update()
{
	m_frame++;
	m_velY += 0.3f;
	m_posX += m_velX;
	m_posY += m_velY;

	if (m_frame > 15)
	{
		if (alpha > 0)
		{
			if (alpha <= decrement)
			{
				alpha = 0;
				dead = true;
			}
			else
			{
				alpha -= decrement;
			}
		}
	}
}

/// <summary>
/// Particle draw function draw the particle to the screen
/// </summary>
/// <param name="cam">Pointer to the game camera to take into account scrolling world</param>
void Particle::draw(Camera * cam)
{
	auto bounds = cam->getBounds();
	dstrect = { (int)m_posX - bounds.x, (int)m_posY - bounds.y, m_width, m_height };
	SDL_SetRenderDrawColor(m_rend, color.r, color.g, color.b, alpha);
	SDL_RenderFillRect(m_rend, &dstrect);
}

/// <summary>
/// Function return bool indicating whether the particle is currently active
/// </summary>
/// <returns>Bool, is the particle dead</returns>
bool Particle::isDead()
{
	return dead;
}

/// <summary>
/// Function allows the particle alpha decrement value to be set
/// </summary>
/// <param name="num">Uint8 decrement value Uint8(0-255)</param>
void Particle::setDecrement(Uint8 num)
{
	decrement = num;
}
