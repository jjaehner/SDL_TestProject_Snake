#include "SnakeBodyPiece.h"


SnakeBodyPiece::SnakeBodyPiece(SnakeBodyPiece* parentBodyPiece, Uint32 bodyIndex, std::string path, SDL_Renderer* renderer, Vector2D position, Vector2D gridLocation)
	: TextureObject(path, renderer, position, gridLocation)
{
	_parentBodyPiece = parentBodyPiece;
	_bodyIndex = bodyIndex;
	_hasMovedFromSpawn = false;
	setSourceRect(0, 0, 64, 64);
	setPosition(position);
	_isStuck = false;
	if (_parentBodyPiece != nullptr)
	{
		setLastPosition(getPosition());
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

void SnakeBodyPiece::update(float deltaSeconds)
{
	calculatePosition(false);
	TextureObject::update(deltaSeconds);
}

void SnakeBodyPiece::calculatePosition(bool addMovement)
{
	Vector2D currentPosition;
	Vector2D tempLastPosition = getLastPosition();
	currentPosition = getPosition();
	setLastPosition(currentPosition);
	if (_parentBodyPiece != nullptr)
	{
		float xDiff = _parentBodyPiece->getPosition().x - _lastPosition.x;
		float yDiff = _parentBodyPiece->getPosition().y - _lastPosition.y;
		if (xDiff >= MovementSpeed || xDiff <= -MovementSpeed ||
			yDiff >= MovementSpeed || yDiff <= -MovementSpeed)
		{
			if (currentPosition.x == _parentBodyPiece->getPosition().x &&
				currentPosition.y > _parentBodyPiece->getLastPosition().y)
			{
				changeDirection(MovementDirection::NORTH);
			}
			else if (currentPosition.x == _parentBodyPiece->getLastPosition().x &&
				currentPosition.y < _parentBodyPiece->getLastPosition().y)
			{
				changeDirection(MovementDirection::SOUTH);
			}
			if (currentPosition.x < _parentBodyPiece->getLastPosition().x &&
				currentPosition.y == _parentBodyPiece->getLastPosition().y)
			{
				changeDirection(MovementDirection::EAST);
			}
			else if (currentPosition.x > _parentBodyPiece->getLastPosition().x &&
				currentPosition.y == _parentBodyPiece->getLastPosition().y)
			{
				changeDirection(MovementDirection::WEST);
			}			

			if (addMovement)
			{
				currentPosition = _parentBodyPiece->getLastPosition();
				_hasMovedFromSpawn = true;
			}
		}
	}
	else
	{
		if (addMovement)
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
				default:
					break;
			}
		}
	}
	setPosition(currentPosition);
}

void SnakeBodyPiece::calculateAnimation(Uint32 currentAnimationFrame, Uint32 totalBodyPieces)
{	
	int xFrame = SnakeTailImageIndex;
	int yFrame = 0;

	if (_parentBodyPiece != nullptr)
	{
		if (_parentBodyPiece->getCurrentDirection() == MovementDirection::EAST &&
			getCurrentDirection() == MovementDirection::SOUTH)
		{
			if (_bodyIndex == (totalBodyPieces - 1))
			{
				xFrame = SnakeTailImageIndex;
			}
			else
			{
				xFrame = SnakeCounterClockWiseBodyTurnImageIndex;
			}
			yFrame = GridRotationNinety;
		}
		else if (_parentBodyPiece->getCurrentDirection() == MovementDirection::EAST &&
			getCurrentDirection() == MovementDirection::NORTH)
		{
			if (_bodyIndex == (totalBodyPieces - 1))
			{
				xFrame = SnakeTailImageIndex;
			}
			else
			{
				xFrame = SnakeClockWiseBodyTurnImageIndex;
			}
			yFrame = GridRotationNinety;
		}
		else if (_parentBodyPiece->getCurrentDirection() == MovementDirection::WEST &&
			getCurrentDirection() == MovementDirection::NORTH)
		{
			if (_bodyIndex == (totalBodyPieces - 1))
			{
				xFrame = SnakeTailImageIndex;
			}
			else
			{
				xFrame = SnakeCounterClockWiseBodyTurnImageIndex;
			}
			yFrame = GridRotationTwoSeventy;
		}
		else if (_parentBodyPiece->getCurrentDirection() == MovementDirection::WEST &&
			getCurrentDirection() == MovementDirection::SOUTH)
		{
			if (_bodyIndex == (totalBodyPieces - 1))
			{
				xFrame = SnakeTailImageIndex;
			}
			else
			{
				xFrame = SnakeClockWiseBodyTurnImageIndex;
			}
			yFrame = GridRotationTwoSeventy;
		}
		else if (_parentBodyPiece->getCurrentDirection() == MovementDirection::SOUTH &&
			getCurrentDirection() == MovementDirection::EAST)
		{
			if (_bodyIndex == (totalBodyPieces - 1))
			{
				xFrame = SnakeTailImageIndex;
			}
			else
			{
				xFrame = SnakeClockWiseBodyTurnImageIndex;
			}
			yFrame = GridRotationZero;
		}
		else if (_parentBodyPiece->getCurrentDirection() == MovementDirection::SOUTH &&
			getCurrentDirection() == MovementDirection::WEST)
		{
			if (_bodyIndex == (totalBodyPieces - 1))
			{
				xFrame = SnakeTailImageIndex;
			}
			else
			{
				xFrame = SnakeCounterClockWiseBodyTurnImageIndex;
			}
			yFrame = GridRotationZero;
		}
		else if (_parentBodyPiece->getCurrentDirection() == MovementDirection::NORTH &&
			getCurrentDirection() == MovementDirection::EAST)
		{
			if (_bodyIndex == (totalBodyPieces - 1))
			{
				xFrame = SnakeTailImageIndex;
			}
			else
			{
				xFrame = SnakeCounterClockWiseBodyTurnImageIndex;
			}
			yFrame = GridRotationOneEighty;
		}
		else if (_parentBodyPiece->getCurrentDirection() == MovementDirection::NORTH &&
			getCurrentDirection() == MovementDirection::WEST)
		{
			if (_bodyIndex == (totalBodyPieces - 1))
			{
				xFrame = SnakeTailImageIndex;
			}
			else
			{
				xFrame = SnakeClockWiseBodyTurnImageIndex;
			}
			yFrame = GridRotationOneEighty;
		}
		else if(_parentBodyPiece->getCurrentDirection() == MovementDirection::NORTH &&
			getCurrentDirection() == MovementDirection::NORTH)
		{
			if (_bodyIndex == (totalBodyPieces - 1))
			{
				xFrame = SnakeTailImageIndex;
			}
			else
			{
				xFrame = SnakeStraightBodyImageIndex;
			}
			yFrame = GridRotationOneEighty;
		}
		else if (_parentBodyPiece->getCurrentDirection() == MovementDirection::SOUTH &&
			getCurrentDirection() == MovementDirection::SOUTH)
		{
			if (_bodyIndex == (totalBodyPieces - 1))
			{
				xFrame = SnakeTailImageIndex;
			}
			else
			{
				xFrame = SnakeStraightBodyImageIndex;
			}
			yFrame = GridRotationZero;
		}
		else if (_parentBodyPiece->getCurrentDirection() == MovementDirection::EAST &&
			getCurrentDirection() == MovementDirection::EAST)
		{
			if (_bodyIndex == (totalBodyPieces - 1))
			{
				xFrame = SnakeTailImageIndex;
			}
			else
			{
				xFrame = SnakeStraightBodyImageIndex;
			}
			yFrame = GridRotationNinety;
		}
		else if (_parentBodyPiece->getCurrentDirection() == MovementDirection::WEST &&
			getCurrentDirection() == MovementDirection::WEST)
		{
			if (_bodyIndex == (totalBodyPieces - 1))
			{
				xFrame = SnakeTailImageIndex;
			}
			else
			{
				xFrame = SnakeStraightBodyImageIndex;
			}
			yFrame = GridRotationTwoSeventy;
		}
	}
	else
	{
		xFrame = SnakeHeadImageIndex;
		switch (_currentDirection)
		{
		case MovementDirection::NORTH:
			yFrame = 2;
			break;
		case MovementDirection::SOUTH:
			yFrame = 0;
			break;
		case MovementDirection::EAST:
			yFrame = 1;
			break;
		case MovementDirection::WEST:
			yFrame = 3;
			break;
		default:
			break;
		}
	}

	setSourceRect(xFrame * SnakePixelSize, yFrame * SnakePixelSize, SnakePixelSize, SnakePixelSize);
	setDestinationRect(getPosition().x, getPosition().y, SnakePixelSize, SnakePixelSize);
}

void SnakeBodyPiece::render()
{
	SDL_RenderCopyEx(_renderer, _texturePtr, &_srcRect, &_destRect, 0.0f, NULL, SDL_FLIP_NONE);
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

void SnakeBodyPiece::hasBecomeUnstuck()
{
	_isStuck = false;
}

void SnakeBodyPiece::hasBecomeStuck()
{
	_isStuck = true;
}

bool SnakeBodyPiece::isStuck()
{
	return _isStuck;
}

MovementDirection SnakeBodyPiece::getCurrentDirection()
{
	return _currentDirection;
}