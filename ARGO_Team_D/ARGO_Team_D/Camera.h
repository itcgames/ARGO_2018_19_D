#ifndef CAMERA_H
#define CAMERA_H

#include <SDL_rect.h>
#include "Utils\VectorAPI.h"

class Camera {
public:
	Camera();

	void update(const VectorAPI & boundPosition, const float & rotation);
	void setPosition(const VectorAPI& position);
	void setSize(const VectorAPI& size);
	void setBounds(const SDL_Rect & bounds);
	SDL_Rect getBounds();
	VectorAPI m_position;
private:
	SDL_Rect m_bounds;
	int m_viewOffset;
	float m_weight;
	float m_shake;

	VectorAPI m_offset;

};

#endif //!CAMERA_H