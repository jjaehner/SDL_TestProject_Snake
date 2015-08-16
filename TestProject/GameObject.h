#pragma once

#include "MathUtils.h"
#include <SDL.h>

class GameObject
{
public:
	GameObject(Vector2D position);
	virtual ~GameObject();

	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;

protected:

	Vector2D _position; //float position in 2D space of where the pixel anchor point is. Not sprite, just anchor
};