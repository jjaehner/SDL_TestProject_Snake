#pragma once

#include "TextureObject.h"
#include "MathUtils.h"
#include <string.h>
#include <iostream>

#define SnakeHeadImageIndex 0
#define SnakeStraightBodyImageIndex 1
#define SnakeClockWiseBodyTurnImageIndex 2
#define SnakeCounterClockWiseBodyTurnImageIndex 3
#define SnakeTailImageIndex 4

#define GridRotationZero 0
#define GridRotationNinety 1
#define GridRotationOneEighty 2
#define GridRotationTwoSeventy 3

#define SnakePixelSize 64
#define InitialSnakeBodySize 3
#define IncrimentSnakeBodySize 1

#define MovementSpeed 64.0f
#define MovementDelayInSeconds 0.5f
#define TimePerAnimationFrameInSeconds 0.5f

#define LeftScreenGridWall 0
#define RightScreenGridWall 9
#define TopScreenGridWall 0
#define BottomScreenGridWall 9

#define SnakeHeadIndex 0

class SnakeBodyPiece : public TextureObject
{
public:
	SnakeBodyPiece(SnakeBodyPiece* parentBodyPiece, Uint32 bodyIndex, std::string path, SDL_Renderer* renderer, Vector2D position, Vector2D gridLocation);
	~SnakeBodyPiece();

	Vector2D getNextMovePosition();
	void setSourceRect(int x, int y, int w, int h);
	void setSourceRect(SDL_Rect srcRect);
	void setPosition(Vector2D position);
	void update(float deltaSeconds);
	void calculatePosition(bool addMovement);
	void calculateAnimation(Uint32 currentAnimationFrame, Uint32 totalBodyPieces);
	void render();
	void changeDirection(MovementDirection movementDirection);
	void setLastPosition(Vector2D lastPosition);
	Vector2D getLastPosition();
	bool getHasMovedFromSpawn();
	void hasBecomeUnstuck();
	void hasBecomeStuck();
	bool isStuck();
	MovementDirection getCurrentDirection();

private:

	Vector2D _lastPosition; //anchor point of where the object was, not sprite position
	MovementDirection _currentDirection;
	SnakeBodyPiece* _parentBodyPiece;
	Uint32 _bodyIndex;
	bool _hasMovedFromSpawn;
	bool _isStuck;
};

