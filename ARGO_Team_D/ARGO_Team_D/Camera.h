#ifndef CAMERA_H
#define CAMERA_H

#include <SDL_rect.h>
#include "SdlVector.h"

class Camera {
public:
	Camera();

	void update(const SdlVector & boundPosition, const float & rotation);
	void setPosition(const SdlVector& position);
	void setSize(const SdlVector& size);
	void setBounds(const SDL_Rect & bounds);
	SDL_Rect getBounds();
	SdlVector m_position;
private:
	SDL_Rect m_bounds;
	int m_viewOffset;
	float m_weight;
	float m_shake;

	SdlVector m_offset;

};

#endif //!CAMERA_H