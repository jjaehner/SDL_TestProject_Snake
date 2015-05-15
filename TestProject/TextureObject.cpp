#include "TextureObject.h"


TextureObject::TextureObject(std::string path, SDL_Renderer* renderer)
	: GameObject()
{
	_surfacePtr = IMG_Load(path.c_str());
	_texturePtr = SDL_CreateTextureFromSurface(renderer, _surfacePtr);
	_destRect.x = this->_position.x;
	_destRect.y = this->_position.y;
	_destRect.w = _surfacePtr->w;
	_destRect.h = _surfacePtr->h;
}


TextureObject::~TextureObject()
{
	SDL_FreeSurface(_surfacePtr);
	SDL_DestroyTexture(_texturePtr);
}

void TextureObject::update(float deltaSeconds)
{
	_destRect.x = this->_position.x;
	_destRect.y= this->_position.y;
}

void TextureObject::setPosition(Vector2D newPosition)
{
	_position = newPosition;
}

Vector2D TextureObject::getPosition()
{
	return this->_position;
}

SDL_Rect TextureObject::getCollisionRect()
{
	return _destRect;
}

void TextureObject::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, _texturePtr, nullptr, &_destRect);
}

bool TextureObject::intersectsTextureObject(TextureObject* textureObject)
{
	bool topLeftOfObjectCollides = false;
	bool topRightOfObjectCollides = false;
	bool bottomLeftOfObjectCollides = false;
	bool bottomRightOfObjectCollides = false;

	float textureObjectCollisionLeft = textureObject->getCollisionRect().x;
	float textureObjectCollisionTop = textureObject->getCollisionRect().y;
	float textureObjectCollisionRight = textureObject->getCollisionRect().x + textureObject->getCollisionRect().w;
	float textureObjectCollisionBottom = textureObject->getCollisionRect().y + textureObject->getCollisionRect().h;
	
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
	float collisionLeft = getCollisionRect().x;
	float collisionTop = getCollisionRect().y;
	float collisionRight = getCollisionRect().x + getCollisionRect().w;
	float collisionBottom = getCollisionRect().y + getCollisionRect().h;
		
	if (collisionLeft <= x && collisionRight >= x)
	{
		if (collisionTop <= y && collisionBottom >= y)
		{
			return true;
		}
	}

	return false;
}