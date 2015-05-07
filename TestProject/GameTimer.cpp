#include "GameTimer.h"
#include <sdl.h>

GameTimer::GameTimer()
{
	_frameCheckFrequencyInSeconds = 0.25f;
	_deltaTicks = 0;
	_elapsedTimeInSeconds = 0;
	_deltaSeconds = 0.0f;
	_lastTickCount = SDL_GetTicks();
}


GameTimer::~GameTimer()
{

}

float GameTimer::getFps()
{
	return _frameRate;
}

float GameTimer::getDeltaTime()
{
	return _deltaSeconds;
}

void GameTimer::update()
{
	Uint32 currentTicks = SDL_GetTicks();
	_deltaTicks = currentTicks - _lastTickCount;
	_lastTickCount = currentTicks;
	_deltaSeconds = (float)_deltaTicks / 1000.0f;
	_elapsedTimeInSeconds += _deltaSeconds;
	while (_elapsedTimeInSeconds >= _frameCheckFrequencyInSeconds) {
		_frameRate = 1.0f / _deltaSeconds;
		_elapsedTimeInSeconds -= _frameCheckFrequencyInSeconds;
	}
}