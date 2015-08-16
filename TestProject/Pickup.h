#pragma once
#include "TextureObject.h"
class Pickup : public TextureObject
{
public:
	Pickup(std::string path, SDL_Renderer* renderer, Vector2D position, Vector2D gridLocation);
	~Pickup();

private:
};