#pragma once
#include<Windows.h>
#include<vector>
#include"State.h"
class Character;
class Sprite;
class AttackState : public State
{
public:
	AttackState();
	~AttackState();
public:
	void Init(Character* character);
	void DInit();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();

	void Start();
	void Stop();
};