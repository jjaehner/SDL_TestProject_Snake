#include "GameTimer.h"
#include <sdl.h>

GameTimer::GameTimer()
{
	_frameCheckFrequencyInSeconds = 0.25f;
	_deltaTicks = 0;
	_elapsedTimeInSeconds = 0;
	_deltaSeconds = 0.0f;
	_lastTickCount = SDL_GetTicks();
	start();
}


GameTimer::~GameTimer()
{

}

float GameTimer::getFps()
{
	return _frameRate;
}

void GameTimer::update()
{
	Timer::update();
	while (_elapsedTimeInSeconds >= _frameCheckFrequencyInSeconds) {
		_frameRate = 1.0f / _deltaSeconds;
		_elapsedTimeInSeconds -= _frameCheckFrequencyInSeconds;
	}
}