#include "GameTimer.h"
#include <sdl.h>

GameTimer::GameTimer()
{
	_frameCheckFrequencyInSeconds = SecondsBetweenFPSCheck;
	_deltaTicks = 0;
	_elapsedTimeInSeconds = 0;
	_deltaSeconds = 0.0f;
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
	while (_elapsedTimeInSeconds >= SecondsBetweenFPSCheck) {
		_frameRate = SecondsBetweenFPSCheck / _deltaSeconds;
		_elapsedTimeInSeconds -= _frameCheckFrequencyInSeconds;
	}
}