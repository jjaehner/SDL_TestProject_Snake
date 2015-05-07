#pragma once

#include "GameObject.h"
#include <SDL_image.h>
#include <string>

class TextureObject : public GameObject
{
public:
	TextureObject(std::string path, SDL_Renderer* renderer);
	virtual ~TextureObject();

	void update(float deltaSeconds);
	void render(SDL_Renderer* renderer);

	void setPosition(Vector2D newPosition);
	Vector2D getPosition();

private:

	SDL_Texture* _texturePtr;
	SDL_Surface* _surfacePtr;
	SDL_Rect _destRect;
};

