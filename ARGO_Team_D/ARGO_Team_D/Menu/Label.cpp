#include "Label.h"

Label::Label(const char * string, int x, int y, int w, int h, SDL_Color color, SDL_Renderer * renderer, SDL_Window * window)
{
	rend = renderer;
	if (TTF_Init() < 0)
	{
		std::cout << "Error initialising TTF library" << std::endl;
	}
	const char *path = "ASSETS\\FONTS\\Face Your Fears.ttf";
	arial = TTF_OpenFont(path, 300);

	this->color = color;

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

	this->string = string;

	onScreen = false;
	isTransitioning = false;
	percent = 0;
	doTransition = true;
}

Label::~Label()
{
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}

void Label::draw()
{
	SDL_RenderCopy(rend, message, NULL, &message_rect);
	SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
}

void Label::update()
{

	if (isCheckBoxLabel)
	{

		if (*condition)
		{
			string = "On";
			SDL_DestroyTexture(message);
			surfaceMessage = TTF_RenderText_Blended(arial, string, color);
			message = SDL_CreateTextureFromSurface(rend, surfaceMessage);
			SDL_FreeSurface(surfaceMessage);
		}
		else
		{
			string = "Off";
			SDL_DestroyTexture(message);
			surfaceMessage = TTF_RenderText_Blended(arial, string, color);
			message = SDL_CreateTextureFromSurface(rend, surfaceMessage);
			SDL_FreeSurface(surfaceMessage);
		}
	}


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
		message_rect.x = displayX;
		message_rect.y = displayY;
		message_rect.w = displayWidth;
		message_rect.h = displayHeight;
	}

	if (isTransitioning)
	{
		transition();
	}
}

void Label::transition()
{
	if (doTransition)
	{
		Lerp(displayX, displayY, -200, windowHeight / 2);
	}	
}

void Label::goToTransition()
{
	isTransitioning = true;
}

void Label::reset()
{
	message_rect.x = startPosX;  //controls the rect's x coordinate 
	message_rect.y = startPosY; // controls the rect's y coordinte
	message_rect.w = 0; // controls the width of the rect
	message_rect.h = 0; // controls the height of the rect
	onScreen = false;
	isTransitioning = false;
	percent = 0;
}

void Label::Lerp(int startPosX, int startPosY, int destX, int destY)
{
	percent += 0.05f;
	if (percent >= 1.0f)
	{
		percent = 1.0f;
	}

	message_rect.x = (1.0f - percent) * startPosX + (percent * destX);

	message_rect.y = (1.0f - percent) * startPosY + (percent * destY);

	if (!onScreen)
	{
		message_rect.w = (1.0f - percent) * 0 + (percent * displayWidth);

		message_rect.h = (1.0f - percent) * 0 + (percent * displayHeight);
	}
	else
	{
		message_rect.w = (1.0f - percent) * displayWidth + (percent * 0);

		message_rect.h = (1.0f - percent) * displayHeight + (percent * 0);
	}
}

void Label::setPosition(int x, int y)
{
	displayX = x;
	displayY = y;
}

void Label::doTransitions(bool b)
{
	doTransition = b;
}

void Label::isACheckBoxLabel(bool * b)
{
	isCheckBoxLabel = true;
	condition = b;
}

void Label::setSize(int x, int y)
{
	displayWidth = x;
	displayHeight = y;
	message_rect.w = displayWidth;
	message_rect.h = displayHeight;
}

void Label::setString(std::string s)
{
	SDL_DestroyTexture(message);
	surfaceMessage = TTF_RenderText_Blended(arial, s.c_str(), color);
	message = SDL_CreateTextureFromSurface(rend, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);
}
