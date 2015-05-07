#include "TextureObject.h"


TextureObject::TextureObject(std::string path, SDL_Renderer* renderer) : GameObject()
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

void TextureObject::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, _texturePtr, nullptr, &_destRect);
}