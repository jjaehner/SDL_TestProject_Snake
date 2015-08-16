#pragma once
#include "Timer.h"
#include "Pickup.h"
#include "SnakeObject.h"
#include <SDL.h>
#include <ctime>

class PickupController
{
public:
	PickupController(std::string path, SDL_Renderer* renderer);
	~PickupController();

	Pickup* getPickupObject();
	void resetPickup(SnakeObject* snakeObject);
	void update(float dt);
	void render();

private:

	SDL_Renderer* _renderer;
	Pickup* _pickupObject;
};