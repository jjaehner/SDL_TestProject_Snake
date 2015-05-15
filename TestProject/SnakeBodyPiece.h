#pragma once

#include "TextureObject.h"
#include "MathUtils.h"
#include <string.h>

enum MovementDirection { FOLLOWING, NORTH, SOUTH, EAST, WEST, STUCK };
#define MovementSpeed 66.0f

class SnakeBodyPiece : public TextureObject
{
public:
	SnakeBodyPiece(SnakeBodyPiece* parentBodyPiece, Uint32 bodyIndex, std::string path, SDL_Renderer* renderer);
	~SnakeBodyPiece();

	Vector2D getNextMovePosition();
	void update(float deltaSeconds);
	void changeDirection(MovementDirection movementDirection);
	void setLastPosition(Vector2D lastPosition);
	Vector2D getLastPosition();
	bool getHasMovedFromSpawn();
	MovementDirection getCurrentDirection();

private:

	Vector2D _lastPosition;
	MovementDirection _currentDirection;
	SnakeBodyPiece* _parentBodyPiece;
	Uint32 _bodyIndex;
	bool _hasMovedFromSpawn;
};

