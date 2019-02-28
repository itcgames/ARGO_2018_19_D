#include "Button.h"
#include<iostream>
Button::Button(const char * string,int x, int y, int w, int h, SDL_Color color, SDL_Renderer * renderer, SDL_Window * window)
{
	rend = renderer;
	if (TTF_Init() < 0)
	{
		std::cout << "Error Initialising TTF library" << std::endl;
	}
	const char *path = "ASSETS\\FONTS\\Face Your Fears.ttf";
	arial = TTF_OpenFont(path, 300);
	//arial = TTF_OpenFont("..//ASSETS//FONTS//arial.ttf", 100);

	this->color = color;
	this->focusColor = {255,255,255,255};
	this->nonFocusColor = color;

	displayX = x;
	displayY = y;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	startPosX = windowWidth + 200;
	startPosY = windowHeight / 2;

	displayWidth = w;
	displayHeight = h;

	surfaceMessage = TTF_RenderText_Blended(arial, string, color);
	message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	message_rect.x = startPosX;  //controls the rect's x coordinate 
	message_rect.y = startPosY; // controls the rect's y coordinte
	message_rect.w = 0; // controls the width of the rect
	message_rect.h = 0; // controls the height of the rect

	r.x = message_rect.x - 5;
	r.y = message_rect.y - 5;
	r.w = w + 20;
	r.h = h + 20;
	alpha = 0;
	this->string= string;
	checkboxString = "Off";

	

	onScreen = false;
	isTransitioning = false;
	percent = 0;
	hasFocus = false;

	doTransition = true;

	isACheckbox = false;
}

Button::~Button()
{
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}

void Button::update()
{

	if (doTransition)
	{
		if (onScreen == false && message_rect.x != displayX && message_rect.y != displayY)
		{
			Lerp(startPosX, startPosY, displayX, displayY);
			if (percent >= 1.0f)
			{
				onScreen = true;
				percent = 0;
			}
		}
	}
	else
	{
		if (m_visible) {
			message_rect.x = displayX;
			message_rect.y = displayY;
			message_rect.w = displayWidth;
			message_rect.h = displayHeight;
			r.x = message_rect.x - 5;
			r.y = message_rect.y - 5;
			r.w = displayWidth + 20;
			r.h = displayHeight + 20;
		}
	}
	if (m_visible) {
		if (hasFocus)
		{
			SDL_DestroyTexture(message);
			color = focusColor;
			surfaceMessage = TTF_RenderText_Blended(arial, string.c_str(), color);
			message = SDL_CreateTextureFromSurface(rend, surfaceMessage);
			SDL_FreeSurface(surfaceMessage);
		}
		else {
			SDL_DestroyTexture(message);
			color = nonFocusColor;
			surfaceMessage = TTF_RenderText_Blended(arial, string.c_str(), color);
			message = SDL_CreateTextureFromSurface(rend, surfaceMessage);
			SDL_FreeSurface(surfaceMessage);
		}
	}

	
	if (isTransitioning)
	{
		transition();
	}
}

void Button::draw()
{
	if (m_visible) {
		SDL_RenderCopy(rend, message, NULL, &message_rect);
		SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
		SDL_RenderDrawRect(rend, &r);
	}
}

void Button::mousePress()
{
	if (m_visible) {
		if (hasFocus)
		{
			if (!isACheckbox)
			{
				std::cout << string << " pressed" << std::endl;
				isTransitioning = true;
				isClicked = true;
			}
			else
			{
				*condition = !(*condition);

				if (*condition)
				{
					checkboxString = "On";
				}
				else
				{
					checkboxString = "Off";
				}
			}

			if (!doTransition)
			{
				try
				{
					Enter();
				}
				catch (std::bad_function_call)
				{
					std::cout << string << " bad function call" << std::endl;
				}
				activateFunction = true;
			}

		}
	}
}

void Button::transition()
{
	if (doTransition)
	{
		Lerp(displayX, displayY, -200, windowHeight / 2);
	}
}

void Button::goToTransition()
{
	isTransitioning = true;
}

void Button::reset()
{
	//onScreen && percent >= 1.0f && isClicked && !activateFunction

	message_rect.x = startPosX;  //controls the rect's x coordinate 
	message_rect.y = startPosY; // controls the rect's y coordinte
	message_rect.w = 0; // controls the width of the rect
	message_rect.h = 0; // controls the height of the rect
	onScreen = false;
	isTransitioning = false;
	percent = 0;
	hasFocus = false;
	isClicked = false;
	m_visible = true;
}

void Button::getMouseCollision(int x, int y)
{

	if(x + 1 > r.x &&
		y + 1 > r.y &&
		r.x + r.w > x &&
		r.y + r.h > y)
	{
		hasFocus = true;
	}
	else {
		hasFocus = false;
	}

}


void Button::Lerp(int startPosX, int startPosY, int destX, int destY)
{
	percent += 0.05f;
	if (percent >= 1.0f)
	{
		percent = 1.0f;
	}

	message_rect.x = (1.0f - percent) * startPosX + (percent * destX);
	r.x = message_rect.x - 5;

	message_rect.y = (1.0f - percent) * startPosY + (percent * destY);
	r.y = message_rect.y - 5;

	if (!onScreen)
	{
		message_rect.w = (1.0f - percent) * 0 + (percent * displayWidth);
		r.w = message_rect.w + 10;

		message_rect.h = (1.0f - percent) * 0 + (percent * displayHeight);
		r.h = message_rect.h + 10;
	}
	else
	{
		message_rect.w = (1.0f - percent) * displayWidth + (percent * 0);
		r.w = message_rect.w + 10;

		message_rect.h = (1.0f - percent) * displayHeight + (percent * 0);
		r.h = message_rect.h + 10;
	}

	if (onScreen && percent >= 1.0f && isClicked)
	{
		try
		{
			Enter();
		}
		catch (std::bad_function_call)
		{
			std::cout <<string <<" bad function call" << std::endl;
		}
		activateFunction = true;
	}
}

void Button::Focus(bool b)
{
	hasFocus = b;
}

void Button::setPosition(int x, int y)
{
	displayX = x;
	displayY = y;
}

void Button::doTransitions(bool b)
{
	doTransition = b;
}

void Button::makeCheckbox(bool * b)
{
	isACheckbox = true;
	condition = b;
}
