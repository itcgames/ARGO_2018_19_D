#include "Hud.h"

Hud::Hud(Camera & cam, SDL_Renderer & rend, SDL_Window * window):
	m_cam{cam}
{
	this->rend = &rend;
	if (TTF_Init() < 0)
	{
		//std::cout << "error error error" << std::endl;
	}
	const char *path = "ASSETS\\FONTS\\BloodBlocks.ttf";
	arial = TTF_OpenFont(path, 150);

	this->color = {255,0,0,255};

	
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	string = "Health : " + std::to_string(100);
	std::cout << string.c_str() << std::endl;

	surfaceMessage = TTF_RenderText_Blended(arial, string.c_str(), color);
	message = SDL_CreateTextureFromSurface(this->rend, surfaceMessage);
	message_rect.x = float(m_cam.m_position.x - float(m_cam.getBounds().x)) - (900.0f / m_cam.m_scale.x);
	message_rect.y = float(m_cam.m_position.y - float(m_cam.getBounds().y)) - (500.0f / m_cam.m_scale.y);

	message_rect.w = 500.0f / m_cam.m_scale.x;
	message_rect.h = 100.0f / m_cam.m_scale.y;





	srcrect = { 0, 0, 64, 64 };
	dstrect = { 0, 0, 64, 64 };
	dstrect2 = { 0, 0, 64, 64 };
	dstrect3 = { 0, 0, 64, 64 };

	image = IMG_Load("ASSETS/IMAGES/heart.png");
	texture = SDL_CreateTextureFromSurface(this->rend, image);

	if (!texture)
	{
		//std::cout << name << " texture failed to load!" << std::endl;
	}

	
}

Hud::~Hud()
{
}

void Hud::update()
{
	message_rect.x = float(m_cam.m_position.x - float(m_cam.getBounds().x)) - (900.0f / m_cam.m_scale.x);
	message_rect.y = float(m_cam.m_position.y - float(m_cam.getBounds().y)) - (500.0f / m_cam.m_scale.y);
	
	message_rect.w = 500.0f / m_cam.m_scale.x;
	message_rect.h = 100.0f / m_cam.m_scale.y;

	dstrect.x = float(m_cam.m_position.x - float(m_cam.getBounds().x)) - (900.0f / m_cam.m_scale.x);
	dstrect.y = float(m_cam.m_position.y - float(m_cam.getBounds().y)) - (400.0f / m_cam.m_scale.y);
	dstrect.w = 64.0f / m_cam.m_scale.x;
	dstrect.h = 64.0f / m_cam.m_scale.y;


	dstrect2.x = float(m_cam.m_position.x - float(m_cam.getBounds().x)) - (800.0f / m_cam.m_scale.x);
	dstrect2.y = float(m_cam.m_position.y - float(m_cam.getBounds().y)) - (400.0f / m_cam.m_scale.y);
	dstrect2.w = 64.0f / m_cam.m_scale.x;
	dstrect2.h = 64.0f / m_cam.m_scale.y;


	dstrect3.x = float(m_cam.m_position.x - float(m_cam.getBounds().x)) - (700.0f / m_cam.m_scale.x);
	dstrect3.y = float(m_cam.m_position.y - float(m_cam.getBounds().y)) - (400.0f / m_cam.m_scale.y);
	dstrect3.w = 64.0f / m_cam.m_scale.x;
	dstrect3.h = 64.0f / m_cam.m_scale.y;
	//std::cout << message_rect.x << " , " << message_rect.y << std::endl;

	/*message_rect.x = this->m_cam.m_position.x;
	message_rect.y = this->m_cam.m_position.y;*/

	/*SDL_DestroyTexture(message);
	color = { 255,0,0,255 };
	surfaceMessage = TTF_RenderText_Blended(arial, string, color);
	message = SDL_CreateTextureFromSurface(rend, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);*/



}

void Hud::draw()
{
	SDL_RenderCopy(rend, message, NULL, &message_rect);
	SDL_RenderCopy(rend, texture, &srcrect, &dstrect);
	SDL_RenderCopy(rend, texture, &srcrect, &dstrect2);
	SDL_RenderCopy(rend, texture, &srcrect, &dstrect3);
	SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
}
