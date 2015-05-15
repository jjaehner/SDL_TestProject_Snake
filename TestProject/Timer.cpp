#include "Timer.h"


Timer::Timer()
{
	_isRunning = false;
	_lastTickCount = SDL_GetTicks();
}


Timer::~Timer()
{
}

void Timer::start()
{
	if (!_isRunning)
	{
		reset();
	}
	_isRunning = true;
}

void Timer::stop()
{
	pause();
	reset();
}

void Timer::pause()
{
	_isRunning = false;
}

void Timer::reset()
{
	_deltaTicks = 0;
	_deltaSeconds = 0.0f;
	_elapsedTimeInSeconds = 0.0f;
}

float Timer::getDeltaTimeInSeconds()
{
	return _deltaSeconds;
}

float Timer::getElapsedTimeInSeconds()
{
	return _elapsedTimeInSeconds;
}

void Timer::update()
{
	if (_isRunning)
	{
		Uint32 currentTicks = SDL_GetTicks();
		_deltaTicks = currentTicks - _lastTickCount;
		_lastTickCount = currentTicks;
		_deltaSeconds = (float)_deltaTicks / 1000.0f;
		_elapsedTimeInSeconds += _deltaSeconds;
	}
}