#include "SnakeObject.h"


SnakeObject::SnakeObject(SDL_Renderer* renderer)
{
	_movementTimer = new Timer();

	_bodyObjects.push_back(new TextureObject("Head.png", renderer));
	_bodyObjects.push_back(new TextureObject("Body.png", renderer));
	_bodyObjects.push_back(new TextureObject("Tail.png", renderer));
	changeDirection(SOUTH);
	_movementTimer->start();
}


SnakeObject::~SnakeObject()
{
	delete _movementTimer;

	while (!_bodyObjects.empty()) {
		auto endObject = _bodyObjects[_bodyObjects.size()-1];
		delete endObject;
		_bodyObjects.pop_back();
	}
}


void SnakeObject::update(float deltaSeconds)
{
	_movementTimer->update();

	if (_movementTimer->getElapsedTimeInSeconds() > 1.0f)
	{
		Vector2D currentOffset;
		switch (_currentDirection)
		{
		case NORTH:
			currentOffset.x = 0.0f;
			currentOffset.y = -MovementSpeed;
			break;
		case SOUTH:
			currentOffset.x = 0.0f;
			currentOffset.y = MovementSpeed;
			break;
		case EAST:
			currentOffset.x = MovementSpeed;
			currentOffset.y = 0.0f;
			break;
		case WEST:
			currentOffset.x = -MovementSpeed;
			currentOffset.y = 0.0f;
			break;
		default:
			break;
		}
		Vector2D currentPosition;
		for (int i = 0; i < _bodyObjects.size(); i++)
		{
			currentPosition = _bodyObjects[i]->getPosition();
			currentPosition.x += currentOffset.x;
			currentPosition.y += currentOffset.y;
			_bodyObjects[i]->setPosition(currentPosition);
			_bodyObjects[i]->update(deltaSeconds);
		}

		_movementTimer->reset();
	}
}

void SnakeObject::render(SDL_Renderer* renderer)
{
	for (int i = 0; i < _bodyObjects.size(); i++)
	{
		_bodyObjects[i]->render(renderer);
	}
}

void SnakeObject::changeDirection(MovementDirection movementDirection)
{
	_currentDirection = movementDirection;
}