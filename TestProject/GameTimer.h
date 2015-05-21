#pragma once
#include "Timer.h"

#define SecondsBetweenFPSCheck 1.0f

class GameTimer : public Timer
{
public:
	GameTimer();
	~GameTimer();
	float getFps();
	void update();

private:
	
	float _frameRate;
	float _frameCheckFrequencyInSeconds;
};