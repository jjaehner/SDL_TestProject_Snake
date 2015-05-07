#include "SnakeObject.h"


SnakeObject::SnakeObject(SDL_Renderer* renderer)
{
	_bodyObjects.push_back(new TextureObject("Head.png", renderer));
	_bodyObjects.push_back(new TextureObject("Body.png", renderer));
	_bodyObjects.push_back(new TextureObject("Tail.png", renderer));
	changeDirection(SOUTH);
}


SnakeObject::~SnakeObject()
{
	while (!_bodyObjects.empty()) {
		auto endObject = _bodyObjects.end();
		delete *endObject;
		_bodyObjects.erase(endObject);
	}
}


void SnakeObject::update(float deltaSeconds)
{
	Vector2D currentOffset;
	switch (_currentDirection)
	{
	case NORTH:
		currentOffset.x = 0.0f;
		currentOffset.y = -MovementSpeed * deltaSeconds;
		break;
	case SOUTH:
		currentOffset.x = 0.0f;
		currentOffset.y = MovementSpeed * deltaSeconds;
		break;
	case EAST:
		currentOffset.x = MovementSpeed * deltaSeconds;
		currentOffset.y = 0.0f;
		break;
	case WEST:
		currentOffset.x = -MovementSpeed * deltaSeconds;
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