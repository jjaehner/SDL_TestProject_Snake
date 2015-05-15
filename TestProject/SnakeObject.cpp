#include "SnakeObject.h"


SnakeObject::SnakeObject(SDL_Renderer* renderer)
{
	_renderer = renderer;
	_movementTimer = new Timer();
	createSnake();
}


SnakeObject::~SnakeObject()
{
	delete _movementTimer;
	destroySnake();
}

void SnakeObject::createSnake()
{
	addBodyLink(3);
	changeDirection(SOUTH);
	_movementTimer->start();
	_gridLocationX = 0;
	_gridLocationY = 0;
	_bodyPartAddDelay = 0;
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

	if (_movementTimer->getElapsedTimeInSeconds() > 1.0f / 2.0f)
	{
		if (_bodyObjects[0]->getCurrentDirection() == NORTH &&
			_gridLocationY == 0)
		{
			_bodyObjects[0]->changeDirection(STUCK);
		}
		else if (_bodyObjects[0]->getCurrentDirection() == SOUTH &&
			_gridLocationY == 9)
		{
			_bodyObjects[0]->changeDirection(STUCK);
		}
		else if (_bodyObjects[0]->getCurrentDirection() == WEST &&
			_gridLocationX == 0)
		{
			_bodyObjects[0]->changeDirection(STUCK);
		}
		else if (_bodyObjects[0]->getCurrentDirection() == EAST &&
			_gridLocationX == 9)
		{
			_bodyObjects[0]->changeDirection(STUCK);
		}

		if (_bodyObjects[0]->getCurrentDirection() != STUCK)
		{
			for (int i = 0; i < _bodyObjects.size(); i++)
			{
				_bodyObjects[i]->update(deltaSeconds);
			}
			_bodyPartAddDelay++;
			if (_bodyPartAddDelay >= 10)
			{
				addBodyLink(1);
				_bodyObjects[_bodyObjects.size() - 1]->update(deltaSeconds);
				_bodyPartAddDelay = 0;
			}
		}

		if (_bodyObjects[0]->getCurrentDirection() == NORTH)
		{
			_gridLocationY -= 1;
		}
		else if (_bodyObjects[0]->getCurrentDirection() == SOUTH)
		{
			_gridLocationY += 1;
		}
		else if (_bodyObjects[0]->getCurrentDirection() == WEST)
		{
			_gridLocationX -= 1;
		}
		else if (_bodyObjects[0]->getCurrentDirection() == EAST)
		{
			_gridLocationX += 1;
		}

		bool gameOver = false;

		for (int i = 1; i < _bodyObjects.size(); i++)
		{
			if (_bodyObjects[0]->intersectsTextureObject(_bodyObjects[i]) &&
				_bodyObjects[i]->getHasMovedFromSpawn() &&
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
	if (linkCount < 1)
	{
		return;
	}
	if (linkCount > 20)
	{
		linkCount = 20;
	}
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
		_bodyObjects[0]->changeDirection(movementDirection);
	}
}