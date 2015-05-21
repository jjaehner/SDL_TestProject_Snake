#include "SnakeBodyPiece.h"


SnakeBodyPiece::SnakeBodyPiece(SnakeBodyPiece* parentBodyPiece, Uint32 bodyIndex, std::string path, SDL_Renderer* renderer)
	: TextureObject(path, renderer)
{
	_parentBodyPiece = parentBodyPiece;
	_bodyIndex = bodyIndex;
	_hasMovedFromSpawn = false;
	_renderAngle = 0.0;
	setSourceRect(0, 0, 64, 64);
	if (_parentBodyPiece != nullptr)
	{
		setPosition(_parentBodyPiece->getPosition());
		setLastPosition(getPosition());
		changeDirection(MovementDirection::FOLLOWING);
	}
}


SnakeBodyPiece::~SnakeBodyPiece()
{
	if (_parentBodyPiece != nullptr)
	{
		delete _parentBodyPiece;
	}
}

Vector2D SnakeBodyPiece::getNextMovePosition()
{
	Vector2D nextMovePosition;
	nextMovePosition.x = this->_position.x;
	nextMovePosition.y = this->_position.y;

	if (_parentBodyPiece != nullptr)
	{
		nextMovePosition = _parentBodyPiece->getPosition();
	}

	return nextMovePosition;
}

void SnakeBodyPiece::setSourceRect(int x, int y, int w, int h)
{
	SDL_Rect srcRect;
	srcRect.x = x;
	srcRect.y = y;
	srcRect.w = w;
	srcRect.h = h;
	setSourceRect(srcRect);
}

void SnakeBodyPiece::setSourceRect(SDL_Rect srcRect)
{
	_srcRect = srcRect;
}

void SnakeBodyPiece::setPosition(Vector2D position)
{
	TextureObject::setPosition(position);
	setDestinationRect(position.x, position.y, SnakePixelSize, SnakePixelSize);
}

void SnakeBodyPiece::setDestinationRect(int x, int y, int w, int h)
{
	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;
	destRect.w = w;
	destRect.h = h;
	setDestinationRect(destRect);
}

void SnakeBodyPiece::setDestinationRect(SDL_Rect destRect)
{
	_destRect = destRect;
}

void SnakeBodyPiece::update(float deltaSeconds)
{
	calculatePosition(deltaSeconds);
	TextureObject::update(deltaSeconds);
}

void SnakeBodyPiece::calculatePosition(float deltaSeconds)
{
	Vector2D currentPosition;
	Vector2D tempLastPosition = getLastPosition();
	currentPosition = getPosition();
	setLastPosition(currentPosition);
	if (_parentBodyPiece != nullptr &&
		_parentBodyPiece->getCurrentDirection() != MovementDirection::STUCK &&
		_currentDirection == MovementDirection::FOLLOWING)
	{
		float xDiff = _parentBodyPiece->getPosition().x - _lastPosition.x;
		float yDiff = _parentBodyPiece->getPosition().y - _lastPosition.y;
		if (xDiff >= MovementSpeed || xDiff <= -MovementSpeed ||
			yDiff >= MovementSpeed || yDiff <= -MovementSpeed)
		{
			currentPosition = _parentBodyPiece->getLastPosition();
			_hasMovedFromSpawn = true;
		}
	}
	else if (_currentDirection != MovementDirection::FOLLOWING &&
		_currentDirection != MovementDirection::STUCK)
	{
		switch (_currentDirection)
		{
		case MovementDirection::NORTH:
			currentPosition.y -= MovementSpeed;
			break;
		case MovementDirection::SOUTH:
			currentPosition.y += MovementSpeed;
			break;
		case MovementDirection::EAST:
			currentPosition.x += MovementSpeed;
			break;
		case MovementDirection::WEST:
			currentPosition.x -= MovementSpeed;
			break;
		case MovementDirection::FOLLOWING:
		default:
			break;
		}
	}
	setPosition(currentPosition);
}

void SnakeBodyPiece::calculateAnimation(float deltaSeconds, Uint32 currentAnimationFrame)
{
	if (_parentBodyPiece != nullptr &&
		_parentBodyPiece->getCurrentDirection() != MovementDirection::STUCK &&
		_currentDirection == MovementDirection::FOLLOWING)
	{
		float xDiff = _parentBodyPiece->getPosition().x - _lastPosition.x;
		float yDiff = _parentBodyPiece->getPosition().y - _lastPosition.y;
		if (xDiff >= MovementSpeed || xDiff <= -MovementSpeed ||
			yDiff >= MovementSpeed || yDiff <= -MovementSpeed)
		{
			if (xDiff > 0.0f)
			{
				_renderAngle = 90.0f;
			}
			else if (xDiff < 0.0f)
			{
				_renderAngle = 270.0f;
			}
			if (yDiff > 0.0f)
			{
				_renderAngle = 180.0f;
			}
			if (yDiff < 0.0f)
			{
				_renderAngle = 0.0f;
			}
		}
	}
	else if (_currentDirection != MovementDirection::FOLLOWING &&
		_currentDirection != MovementDirection::STUCK)
	{
		switch (_currentDirection)
		{
		case MovementDirection::NORTH:
			_renderAngle = 0.0;
			break;
		case MovementDirection::SOUTH:
			_renderAngle = 180.0;
			break;
		case MovementDirection::EAST:
			_renderAngle = 90.0;
			break;
		case MovementDirection::WEST:
			_renderAngle = 270.0;
			break;
		case MovementDirection::FOLLOWING:
		default:
			break;
		}
	}

	int xFrame = currentAnimationFrame / 6;
	int yFrame = currentAnimationFrame % 6;

	setSourceRect(xFrame * SnakePixelSize, yFrame * SnakePixelSize, SnakePixelSize, SnakePixelSize);
	setDestinationRect(getPosition().x, getPosition().y, SnakePixelSize, SnakePixelSize);
}

void SnakeBodyPiece::render(SDL_Renderer* renderer)
{
	SDL_RenderCopyEx(renderer, _texturePtr, &_srcRect, &_destRect, _renderAngle, NULL, SDL_FLIP_NONE);
}

void SnakeBodyPiece::changeDirection(MovementDirection movementDirection)
{
	_currentDirection = movementDirection;
}

void SnakeBodyPiece::setLastPosition(Vector2D lastPosition)
{
	_lastPosition.x = lastPosition.x;
	_lastPosition.y = lastPosition.y;
}

Vector2D SnakeBodyPiece::getLastPosition()
{
	return _lastPosition;
}

bool SnakeBodyPiece::getHasMovedFromSpawn()
{
	return _hasMovedFromSpawn;
}

MovementDirection SnakeBodyPiece::getCurrentDirection()
{
	return _currentDirection;
}