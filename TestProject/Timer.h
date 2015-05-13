#pragma once

#include <SDL.h>

class Timer
{
public:
	Timer();
	~Timer();

	void update();
	float getDeltaTimeInSeconds();
	float getElapsedTimeInSeconds();
	void start();
	void stop();
	void pause();
	void reset();

protected:

	bool _isRunning;
	unsigned long _lastTickCount;
	unsigned int _deltaTicks;
	float _deltaSeconds;
	float _elapsedTimeInSeconds;
};