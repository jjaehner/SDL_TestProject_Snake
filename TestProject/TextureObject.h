#pragma once

#include "GameObject.h"
#include <SDL_image.h>
#include <string>

enum class MovementDirection {
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

class TextureObject : public GameObject
{
public:
	TextureObject(std::string path, SDL_Renderer* renderer, Vector2D position, Vector2D gridLocation);
	virtual ~TextureObject();

	void update(float deltaSeconds);
	void render();
	
	virtual void setPosition(Vector2D newPosition);
	Vector2D getPosition();
	void setDestinationRect(int x, int y, int w, int h);
	void setDestinationRect(SDL_Rect destRect);
	SDL_Rect getDestinationRect();
	bool intersectsTextureObject(TextureObject* textureObject);
	bool intersectsGridObject(TextureObject* textureObject);
	Vector2D getGridLocation();
	void setGridLocation(Vector2D newGridLocation);
	void updateGridLocation(MovementDirection movementDirection);


protected:

	SDL_Renderer* _renderer;
	SDL_Texture* _texturePtr;
	SDL_Surface* _surfacePtr;
	SDL_Rect _srcRect; //pixels from source image to draw (will scale to dest rect size)
	SDL_Rect _destRect; //what pixels on the rendering background to fill with src rect), will be built on position
	bool pointIsInside(float x, float y);
	Vector2D _gridLocation;
};

