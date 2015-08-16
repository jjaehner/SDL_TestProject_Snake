#include "SnakeObject.h"
#include <iostream>


SnakeObject::SnakeObject(SDL_Renderer* renderer)
{
	_renderer = renderer;
	_movementTimer = new Timer();
	_animationTimer = new Timer();
	_initialSnakeCreated = false;
	createSnake();
}


SnakeObject::~SnakeObject()
{
	delete _movementTimer;
	delete _animationTimer;
	destroySnake();
}

void SnakeObject::createSnake()
{
	addBodyLink(InitialSnakeBodySize);
	changeDirection(MovementDirection::SOUTH);
	_movementTimer->start();
	_animationTimer->start();
	_currentAnimationFrame = 0;
	_decrementalMovementDelay = MovementDelayInSeconds;
	_initialSnakeCreated = true;
	animate();
}

void SnakeObject::destroySnake()
{
	if (!_bodyObjects.empty())
	{
		auto deleteFromTail = _bodyObjects[_bodyObjects.size() - 1];
		delete deleteFromTail;
	}

	while (!_bodyObjects.empty()) {
		if (_bodyObjects[_bodyObjects.size() - 1] != nullptr)
		{
			_bodyObjects.pop_back();
		}
	}
	_initialSnakeCreated = false;
}

void SnakeObject::update(float deltaSeconds)
{
	_movementTimer->update();
	_animationTimer->update();
	bool updateMovement = _movementTimer->getElapsedTimeInSeconds() > _decrementalMovementDelay;
	if (updateMovement)
	{
		_movementTimer->reset();
	}
	
	if (_bodyObjects[SnakeHeadIndex]->getCurrentDirection() == MovementDirection::NORTH &&
		_bodyObjects[SnakeHeadIndex]->getGridLocation().y <= TopScreenGridWall)
	{
		_bodyObjects[SnakeHeadIndex]->hasBecomeStuck();
	}
	else if (_bodyObjects[SnakeHeadIndex]->getCurrentDirection() == MovementDirection::SOUTH &&
		_bodyObjects[SnakeHeadIndex]->getGridLocation().y >= BottomScreenGridWall)
	{
		_bodyObjects[SnakeHeadIndex]->hasBecomeStuck();
	}
	else if (_bodyObjects[SnakeHeadIndex]->getCurrentDirection() == MovementDirection::WEST &&
		_bodyObjects[SnakeHeadIndex]->getGridLocation().x <= LeftScreenGridWall)
	{
		_bodyObjects[SnakeHeadIndex]->hasBecomeStuck();
	}
	else if (_bodyObjects[SnakeHeadIndex]->getCurrentDirection() == MovementDirection::EAST &&
		_bodyObjects[SnakeHeadIndex]->getGridLocation().x >= RightScreenGridWall)
	{
		_bodyObjects[SnakeHeadIndex]->hasBecomeStuck();
	}
	else
	{
		_bodyObjects[SnakeHeadIndex]->hasBecomeUnstuck();
	}

	if (_bodyObjects[SnakeHeadIndex]->isStuck() == false)
	{
		for (int i = 0; i < _bodyObjects.size(); i++)
		{
			_bodyObjects[i]->calculatePosition(updateMovement);
		}
		if (updateMovement)
		{
			for (int i = 0; i < _bodyObjects.size(); i++)
			{
				if (_bodyObjects[i]->getCurrentDirection() == MovementDirection::NORTH)
				{
					_bodyObjects[i]->updateGridLocation(MovementDirection::NORTH);
				}
				else if (_bodyObjects[i]->getCurrentDirection() == MovementDirection::SOUTH)
				{
					_bodyObjects[i]->updateGridLocation(MovementDirection::SOUTH);
				}
				else if (_bodyObjects[i]->getCurrentDirection() == MovementDirection::WEST)
				{
					_bodyObjects[i]->updateGridLocation(MovementDirection::WEST);
				}
				else if (_bodyObjects[i]->getCurrentDirection() == MovementDirection::EAST)
				{
					_bodyObjects[i]->updateGridLocation(MovementDirection::EAST);
				}
			}
			animate();
		}
	}

	bool gameOver = false;

	for (int i = 1; i < _bodyObjects.size(); i++)
	{
		if (_bodyObjects[i]->getHasMovedFromSpawn() &&
			_bodyObjects[SnakeHeadIndex]->intersectsGridObject(_bodyObjects[i]) &&
			!gameOver)
		{
			gameOver = true;
			break;
		}
	}

	if (gameOver)
	{
		destroySnake();
		createSnake();
		return;
	}
}

void SnakeObject::animate()
{
	if (_animationTimer->getElapsedTimeInSeconds() > 1.0f / 10.0f)
	{
		_currentAnimationFrame++;
		if (_currentAnimationFrame == 6 * 6)
		{
			_currentAnimationFrame = 0;
		}
		_animationTimer->reset();
	}

	for (int i = 0; i < _bodyObjects.size(); i++)
	{
		_bodyObjects[i]->calculateAnimation(_currentAnimationFrame, _bodyObjects.size());
	}
}

void SnakeObject::render()
{
	for (int i = _bodyObjects.size() - 1; i > -1; i--)
	{
		_bodyObjects[i]->render();
	}
}

void SnakeObject::gatherPickup()
{
	_decrementalMovementDelay *= 0.98f;
	addBodyLink(IncrimentSnakeBodySize);
	_bodyObjects[_bodyObjects.size() - 1]->calculatePosition(false);
	animate();
}

void SnakeObject::addBodyLink(Uint32 linkCount)
{
	Vector2D position;
	Vector2D gridLocation;
	if (_bodyObjects.size() == 0)
	{		
		position.x = InitialGridSpawnX * 64;
		position.y = InitialGridSpawnY * 64;		
		gridLocation.x = InitialGridSpawnX;
		gridLocation.y = InitialGridSpawnY;
		_bodyObjects.push_back(new SnakeBodyPiece(nullptr, 0, "SnakeTiles.png", _renderer, position, gridLocation));
		linkCount--;
	}
	for (int i = 0; i < linkCount; i++)
	{
		if (!_initialSnakeCreated)
		{
			position.x = _bodyObjects[0]->getPosition().x;
			position.y = _bodyObjects[0]->getPosition().y - (64 * (i + 1));
		}
		else
		{
			position = _bodyObjects[_bodyObjects.size() - 1]->getLastPosition();
		}
		gridLocation.x = position.x / 64.0f;
		gridLocation.y = position.y / 64.0f;
		_bodyObjects.push_back(new SnakeBodyPiece(_bodyObjects[_bodyObjects.size() - 1], _bodyObjects.size(), "SnakeTiles.png", _renderer, position, gridLocation));
		if ((_bodyObjects[_bodyObjects.size() - 1]->getPosition().x == _bodyObjects[_bodyObjects.size() - 2]->getPosition().x) &&
			(_bodyObjects[_bodyObjects.size() - 1]->getPosition().y < _bodyObjects[_bodyObjects.size() - 2]->getPosition().y))
		{
			_bodyObjects[_bodyObjects.size() - 1]->changeDirection(MovementDirection::SOUTH);
		}
		else if ((_bodyObjects[_bodyObjects.size() - 1]->getPosition().x == _bodyObjects[_bodyObjects.size() - 2]->getPosition().x) &&
			(_bodyObjects[_bodyObjects.size() - 1]->getPosition().y > _bodyObjects[_bodyObjects.size() - 2]->getPosition().y))
		{
			_bodyObjects[_bodyObjects.size() - 1]->changeDirection(MovementDirection::NORTH);
		}
		else if ((_bodyObjects[_bodyObjects.size() - 1]->getPosition().x < _bodyObjects[_bodyObjects.size() - 2]->getPosition().x) &&
			(_bodyObjects[_bodyObjects.size() - 1]->getPosition().y == _bodyObjects[_bodyObjects.size() - 2]->getPosition().y))
		{
			_bodyObjects[_bodyObjects.size() - 1]->changeDirection(MovementDirection::EAST);
		}
		else if ((_bodyObjects[_bodyObjects.size() - 1]->getPosition().x > _bodyObjects[_bodyObjects.size() - 2]->getPosition().x) &&
			(_bodyObjects[_bodyObjects.size() - 1]->getPosition().y == _bodyObjects[_bodyObjects.size() - 2]->getPosition().y))
		{
			_bodyObjects[_bodyObjects.size() - 1]->changeDirection(MovementDirection::WEST);
		}
	}
}

void SnakeObject::changeDirection(MovementDirection movementDirection)
{
	if (_bodyObjects.size() > 0 && _bodyObjects[0] != nullptr)
	{
		_bodyObjects[SnakeHeadIndex]->changeDirection(movementDirection);
	}
}

bool SnakeObject::intersectsGridObject(TextureObject* obj)
{
	return _bodyObjects[SnakeHeadIndex]->intersectsGridObject(obj);
}

std::vector<Vector2D> SnakeObject::getSnakeBodyPiecesGridIndex()
{
	std::vector<Vector2D> indicies;

	for (int i = 0; i < _bodyObjects.size(); i++)
	{
		indicies.push_back(_bodyObjects[i]->getGridLocation());
	}

	return indicies;
}