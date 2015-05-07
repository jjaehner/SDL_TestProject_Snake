#pragma once
#include "TextureObject.h"
#include <SDL.h>
#include <vector>

enum MovementDirection { NORTH, SOUTH, EAST, WEST };
#define MovementSpeed 35.0f

class SnakeObject
{
public:
	SnakeObject(SDL_Renderer* renderer);
	~SnakeObject();
	void update(float deltaSeconds);
	void render(SDL_Renderer* renderer);

	void changeDirection(MovementDirection movementDirection);

private:

	std::vector<TextureObject*> _bodyObjects;
	MovementDirection _currentDirection;
};