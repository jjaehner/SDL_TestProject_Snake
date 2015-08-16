#include "Pickup.h"


Pickup::Pickup(std::string path, SDL_Renderer* renderer, Vector2D position, Vector2D gridLocation)
	:TextureObject(path, renderer, position, gridLocation)
{
	_srcRect.x = 0;
	_srcRect.y = 64 * 4;
	_srcRect.w = 64;
	_srcRect.h = 64;
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 64;
	rect.h = 64;
	setDestinationRect(rect);
}


Pickup::~Pickup()
{
}