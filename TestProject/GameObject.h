#pragma once

#include "MathUtils.h"
#include <SDL.h>

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void update(float deltaTime) = 0;
	virtual void render(SDL_Renderer* renderer) = 0;

protected:

	Vector2D _position;
};