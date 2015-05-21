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
	
	virtual void setPosition(Vector2D newPosition);
	Vector2D getPosition();
	SDL_Rect getDestinationRect();
	bool intersectsTextureObject(TextureObject* textureObject);


protected:

	SDL_Texture* _texturePtr;
	SDL_Surface* _surfacePtr;
	SDL_Rect _srcRect;
	SDL_Rect _destRect;
	bool pointIsInside(float x, float y);
};

