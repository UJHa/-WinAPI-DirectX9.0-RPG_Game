#pragma once
#include"State.h"
class Character;
class MoveState : public State
{
public:
	MoveState();
	~MoveState();
private:
	float _movingDuration;
public:
	void Init(Character* character);
	void Update(float deltaTime);

	void Start();
	void Stop();
};