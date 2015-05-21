#pragma once

#include "TextureObject.h"
#include "MathUtils.h"
#include <string.h>
#include <iostream>

enum class MovementDirection {
	FOLLOWING = 0,
	NORTH = 1,
	SOUTH = 2,
	EAST = 3,
	WEST = 4,
	STUCK = 5
};

#define InitialGridSpawnX 0
#define InitialGridSpawnY 0

#define SnakePixelSize 64
#define InitialSnakeBodySize 1
#define IncrimentSnakeBodySize 1
#define AddBodyLinkAfterMoveCounterMax 3

#define MovementSpeed 66.0f
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
	SnakeBodyPiece(SnakeBodyPiece* parentBodyPiece, Uint32 bodyIndex, std::string path, SDL_Renderer* renderer);
	~SnakeBodyPiece();

	Vector2D getNextMovePosition();
	void setSourceRect(int x, int y, int w, int h);
	void setSourceRect(SDL_Rect srcRect);
	void setPosition(Vector2D position);
	void setDestinationRect(int x, int y, int w, int h);
	void setDestinationRect(SDL_Rect destRect);	
	void update(float deltaSeconds);
	void calculatePosition(float deltaSeconds);
	void calculateAnimation(float deltaSeconds, Uint32 currentAnimationFrame);
	void render(SDL_Renderer* renderer);
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
	double _renderAngle;
};

