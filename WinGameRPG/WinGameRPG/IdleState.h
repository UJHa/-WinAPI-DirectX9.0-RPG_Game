#pragma once
#include"State.h"
class Character;
class IdleState : public State
{
public:
	IdleState();
	~IdleState();
public:
	void Init(Character* character);
	void Update(float deltaTime);
	void Start();
	void Stop();
};