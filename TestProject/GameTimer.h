#pragma once
#include "Timer.h"

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