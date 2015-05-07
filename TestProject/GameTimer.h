#pragma once
class GameTimer
{
public:
	GameTimer();
	~GameTimer();
	float getFps();
	float getDeltaTime();
	void update();

private:
	
	unsigned long _lastTickCount;
	unsigned int _deltaTicks;
	float _frameRate;
	float _deltaSeconds;
	float _elapsedTimeInSeconds;
	float _frameCheckFrequencyInSeconds;
};

