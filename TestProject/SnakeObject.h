#pragma once
#include "SnakeBodyPiece.h"
#include "Timer.h"
#include <SDL.h>
#include <vector>

#define InitialGridSpawnX 3
#define InitialGridSpawnY 3

class SnakeObject
{
public:
	SnakeObject(SDL_Renderer* renderer);
	~SnakeObject();
	void createSnake();
	void destroySnake();
	void update(float deltaSeconds);
	void animate();
	void render();
	void gatherPickup();
	void addBodyLink(Uint32 linkCount);
	void changeDirection(MovementDirection movementDirection);
	bool intersectsGridObject(TextureObject* obj);
	std::vector<Vector2D> getSnakeBodyPiecesGridIndex();

private:

	bool _initialSnakeCreated;
	std::vector<SnakeBodyPiece*> _bodyObjects;
	Timer* _movementTimer;
	Timer* _animationTimer;
	SDL_Renderer* _renderer;
	Uint32 _currentAnimationFrame;
	float _decrementalMovementDelay;
};