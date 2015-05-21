#include "SnakeObject.h"


SnakeObject::SnakeObject(SDL_Renderer* renderer)
{
	_renderer = renderer;
	_movementTimer = new Timer();
	_animationTimer = new Timer();
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
	_gridLocationX = InitialGridSpawnX;
	_gridLocationY = InitialGridSpawnY;
	_bodyPartAddDelay = 0;
	_currentAnimationFrame = 0;
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
}

void SnakeObject::update(float deltaSeconds)
{
	_movementTimer->update();
	_animationTimer->update();

	if (_movementTimer->getElapsedTimeInSeconds() > MovementDelayInSeconds)
	{
		if (_bodyObjects[SnakeHeadIndex]->getCurrentDirection() == MovementDirection::NORTH &&
			_gridLocationY == TopScreenGridWall)
		{
			_bodyObjects[SnakeHeadIndex]->changeDirection(MovementDirection::STUCK);
		}
		else if (_bodyObjects[SnakeHeadIndex]->getCurrentDirection() == MovementDirection::SOUTH &&
			_gridLocationY == BottomScreenGridWall)
		{
			_bodyObjects[SnakeHeadIndex]->changeDirection(MovementDirection::STUCK);
		}
		else if (_bodyObjects[SnakeHeadIndex]->getCurrentDirection() == MovementDirection::WEST &&
			_gridLocationX == LeftScreenGridWall)
		{
			_bodyObjects[SnakeHeadIndex]->changeDirection(MovementDirection::STUCK);
		}
		else if (_bodyObjects[SnakeHeadIndex]->getCurrentDirection() == MovementDirection::EAST &&
			_gridLocationX == RightScreenGridWall)
		{
			_bodyObjects[SnakeHeadIndex]->changeDirection(MovementDirection::STUCK);
		}

		if (_bodyObjects[SnakeHeadIndex]->getCurrentDirection() != MovementDirection::STUCK)
		{
			for (int i = 0; i < _bodyObjects.size(); i++)
			{
				_bodyObjects[i]->calculatePosition(deltaSeconds);
			}
			_bodyPartAddDelay++;
			if (_bodyPartAddDelay >= AddBodyLinkAfterMoveCounterMax)
			{
				addBodyLink(IncrimentSnakeBodySize);
				_bodyObjects[_bodyObjects.size() - 1]->calculatePosition(deltaSeconds);
				_bodyPartAddDelay = 0;
			}
		}

		if (_bodyObjects[SnakeHeadIndex]->getCurrentDirection() == MovementDirection::NORTH)
		{
			_gridLocationY -= 1;
		}
		else if (_bodyObjects[SnakeHeadIndex]->getCurrentDirection() == MovementDirection::SOUTH)
		{
			_gridLocationY += 1;
		}
		else if (_bodyObjects[SnakeHeadIndex]->getCurrentDirection() == MovementDirection::WEST)
		{
			_gridLocationX -= 1;
		}
		else if (_bodyObjects[SnakeHeadIndex]->getCurrentDirection() == MovementDirection::EAST)
		{
			_gridLocationX += 1;
		}

		bool gameOver = false;

		for (int i = 1; i < _bodyObjects.size(); i++)
		{
			if (_bodyObjects[i]->getHasMovedFromSpawn() &&
				_bodyObjects[SnakeHeadIndex]->intersectsTextureObject(_bodyObjects[i]) &&
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
		}

		_movementTimer->reset();
	}
	
	if (_animationTimer->getElapsedTimeInSeconds() > 1.0f / 60.0f)
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
		_bodyObjects[i]->calculateAnimation(deltaSeconds, _currentAnimationFrame);
	}
}

void SnakeObject::render()
{
	for (int i = _bodyObjects.size() - 1; i > -1; i--)
	{
		_bodyObjects[i]->render(_renderer);
	}
}

void SnakeObject::addBodyLink(Uint32 linkCount)
{
	if (_bodyObjects.size() == 0)
	{
		_bodyObjects.push_back(new SnakeBodyPiece(nullptr, 0, "Head.png", _renderer));
		linkCount--;
	}
	for (int i = 0; i < linkCount; i++)
	{
		_bodyObjects.push_back(new SnakeBodyPiece(_bodyObjects[_bodyObjects.size() - 1], _bodyObjects.size(), "Body.png", _renderer));
	}
}

void SnakeObject::changeDirection(MovementDirection movementDirection)
{
	if (_bodyObjects.size() > 0 && _bodyObjects[0] != nullptr)
	{
		_bodyObjects[SnakeHeadIndex]->changeDirection(movementDirection);
	}
}