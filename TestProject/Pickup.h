#pragma once
#include "TextureObject.h"
class Pickup : public TextureObject
{
public:
	Pickup(std::string path, SDL_Renderer* renderer);
	~Pickup();

	bool intersectsObject(TextureObject textureObject);

private:

	bool pointIsInside(float x, float y);
};

