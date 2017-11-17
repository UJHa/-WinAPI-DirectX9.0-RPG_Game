#pragma once
#include"State.h"
class Character;
class DeadState : public State
{
public:
	DeadState();
	~DeadState();
public:
	void Init(Character* character);
	void DInit();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();

	void Start();
	void Stop();

	void CreateSprite();
};