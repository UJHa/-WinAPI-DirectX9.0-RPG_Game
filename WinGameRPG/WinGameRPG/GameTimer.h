#pragma once
class GameTimer
{
private:
	double _deltaTime;
	__int64 _prevCount;
	double _secondPerCount;
public:
	GameTimer();
	~GameTimer();
	void Reset();
	void Update();
	float GetDeltaTime();
};