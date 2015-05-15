#include "SnakeBodyPiece.h"


SnakeBodyPiece::SnakeBodyPiece(SnakeBodyPiece* parentBodyPiece, Uint32 bodyIndex, std::string path, SDL_Renderer* renderer)
	: TextureObject(path, renderer)
{
	_parentBodyPiece = parentBodyPiece;
	_bodyIndex = bodyIndex;
	_hasMovedFromSpawn = false;
	if (_parentBodyPiece != nullptr)
	{
		setPosition(_parentBodyPiece->getPosition());
		setLastPosition(getPosition());
		changeDirection(FOLLOWING);
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

void SnakeBodyPiece::update(float deltaSeconds)
{
	Vector2D currentPosition;
	currentPosition = getPosition();
	setLastPosition(currentPosition);
	if (_parentBodyPiece != nullptr &&
		_parentBodyPiece->getCurrentDirection() != STUCK &&
		_currentDirection == FOLLOWING)
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
	else if (_currentDirection != FOLLOWING &&
		_currentDirection != STUCK)
	{
		switch (_currentDirection)
		{
		case NORTH:
			currentPosition.y -= MovementSpeed;
			break;
		case SOUTH:
			currentPosition.y += MovementSpeed;
			break;
		case EAST:
			currentPosition.x += MovementSpeed;
			break;
		case WEST:
			currentPosition.x -= MovementSpeed;
			break;
		case FOLLOWING:
		default:
			break;
		}
	}
	setPosition(currentPosition);
	TextureObject::update(deltaSeconds);
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