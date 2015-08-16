#include "PickupController.h"


PickupController::PickupController(std::string path, SDL_Renderer* renderer)
{
	srand(time(0));

	Vector2D position;
	position.x = 0;
	position.y = 0;

	Vector2D gridLocation;
	gridLocation.x = 0;
	gridLocation.y = 0;

	_pickupObject = new Pickup(path, renderer, position, gridLocation);
}

PickupController::~PickupController()
{
	delete _pickupObject;
}

Pickup* PickupController::getPickupObject()
{
	return _pickupObject;
}

void PickupController::resetPickup(SnakeObject* snakeObject)
{
	bool resetDone = false;

	std::vector<Vector2D> reservedGridIndicies = snakeObject->getSnakeBodyPiecesGridIndex();

	Vector2D newPosition;
	newPosition.x = rand() % 10;
	newPosition.y = rand() % 10;

	int attempts = 0;
	for (int i = 0; i < reservedGridIndicies.size(); i++)
	{
		if ((int)newPosition.x == reservedGridIndicies[i].x &&
			(int)newPosition.y == reservedGridIndicies[i].y)
		{
			newPosition.x = rand() % 10;
			newPosition.y = rand() % 10;
			i = 0;
		}
		attempts++;
	}

	std::cout << "Attempts to relocate pickup: " << attempts << std::endl;

	_pickupObject->setGridLocation(newPosition);

	newPosition.x *= 64;
	newPosition.y *= 64;
	_pickupObject->setPosition(newPosition);

	SDL_Rect rect;
	rect.x = newPosition.x;
	rect.y = newPosition.y;
	rect.w = _pickupObject->getDestinationRect().w;
	rect.h = _pickupObject->getDestinationRect().h;
	_pickupObject->setDestinationRect(rect);
}

void PickupController::update(float dt)
{
	_pickupObject->update(dt);
}

void PickupController::render()
{
	_pickupObject->render();
}