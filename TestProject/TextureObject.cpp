#include "TextureObject.h"


TextureObject::TextureObject(std::string path, SDL_Renderer* renderer, Vector2D position, Vector2D gridLocation)
	: GameObject(position)
{
	_renderer = renderer;
	_surfacePtr = IMG_Load(path.c_str());
	_texturePtr = SDL_CreateTextureFromSurface(renderer, _surfacePtr);
	_destRect.x = this->_position.x;
	_destRect.y = this->_position.y;
	_destRect.w = _surfacePtr->w;
	_destRect.h = _surfacePtr->h;
	_gridLocation = gridLocation;
}


TextureObject::~TextureObject()
{
	SDL_FreeSurface(_surfacePtr);
	SDL_DestroyTexture(_texturePtr);
}

void TextureObject::update(float deltaSeconds)
{
	_destRect.x = this->_position.x;
	_destRect.y = this->_position.y;
}

void TextureObject::setPosition(Vector2D newPosition)
{
	_position = newPosition;
}

Vector2D TextureObject::getPosition()
{
	return this->_position;
}

void TextureObject::setDestinationRect(int x, int y, int w, int h)
{
	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;
	destRect.w = w;
	destRect.h = h;
	setDestinationRect(destRect);
}

void TextureObject::setDestinationRect(SDL_Rect destRect)
{
	_destRect = destRect;
}

SDL_Rect TextureObject::getDestinationRect()
{
	return _destRect;
}

void TextureObject::render()
{
	SDL_RenderCopy(_renderer, _texturePtr, &_srcRect, &_destRect);
}

bool TextureObject::intersectsTextureObject(TextureObject* textureObject)
{
	bool topLeftOfObjectCollides = false;
	bool topRightOfObjectCollides = false;
	bool bottomLeftOfObjectCollides = false;
	bool bottomRightOfObjectCollides = false;

	float textureObjectCollisionLeft = textureObject->getDestinationRect().x;
	float textureObjectCollisionTop = textureObject->getDestinationRect().y;
	float textureObjectCollisionRight = textureObject->getDestinationRect().x + textureObject->getDestinationRect().w;
	float textureObjectCollisionBottom = textureObject->getDestinationRect().y + textureObject->getDestinationRect().h;
	
	if (pointIsInside(textureObjectCollisionLeft, textureObjectCollisionTop))
	{
		topLeftOfObjectCollides = true;
	}
	
	if (pointIsInside(textureObjectCollisionRight, textureObjectCollisionTop))
	{
		topRightOfObjectCollides = true;
	}
	
	if (pointIsInside(textureObjectCollisionLeft, textureObjectCollisionBottom))
	{
		bottomLeftOfObjectCollides = true;
	}
	
	if (pointIsInside(textureObjectCollisionRight, textureObjectCollisionBottom))
	{
		bottomRightOfObjectCollides = true;
	}

	if (topLeftOfObjectCollides && topRightOfObjectCollides && bottomLeftOfObjectCollides && bottomRightOfObjectCollides)
	{
		return true;
	}

	return false;
}

bool TextureObject::pointIsInside(float x, float y)
{
	float collisionLeft = getDestinationRect().x;
	float collisionTop = getDestinationRect().y;
	float collisionRight = getDestinationRect().x + getDestinationRect().w;
	float collisionBottom = getDestinationRect().y + getDestinationRect().h;
		
	if (collisionLeft <= x && collisionRight >= x)
	{
		if (collisionTop <= y && collisionBottom >= y)
		{
			return true;
		}
	}

	return false;
}

bool TextureObject::intersectsGridObject(TextureObject* textureObject)
{
	if (_gridLocation.x == textureObject->getGridLocation().x &&
		_gridLocation.y == textureObject->getGridLocation().y)
	{
		return true;
	}
	return false;
}

Vector2D TextureObject::getGridLocation()
{
	return _gridLocation;
}

void TextureObject::setGridLocation(Vector2D newGridLocation)
{
	_gridLocation = newGridLocation;
}

void TextureObject::updateGridLocation(MovementDirection movementDirection)
{
	if (movementDirection == MovementDirection::NORTH)
	{
		_gridLocation.y -= 1.0f;
	}
	else if (movementDirection == MovementDirection::SOUTH)
	{
		_gridLocation.y += 1.0f;
	}
	else if (movementDirection == MovementDirection::WEST)
	{
		_gridLocation.x -= 1.0f;
	}
	else if (movementDirection == MovementDirection::EAST)
	{
		_gridLocation.x += 1.0f;
	}
}