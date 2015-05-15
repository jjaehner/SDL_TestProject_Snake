#pragma once
#include "SnakeBodyPiece.h"
#include "Timer.h"
#include <SDL.h>
#include <vector>

class SnakeObject
{
public:
	SnakeObject(SDL_Renderer* renderer);
	~SnakeObject();
	void createSnake();
	void destroySnake();
	void update(float deltaSeconds);
	void render();
	void addBodyLink(Uint32 linkCount);
	void changeDirection(MovementDirection movementDirection);

private:

	std::vector<SnakeBodyPiece*> _bodyObjects;
	Timer* _movementTimer;
	SDL_Renderer* _renderer;
	Uint32 _gridLocationX;
	Uint32 _gridLocationY;
	Uint32 _bodyPartAddDelay = 0;
};