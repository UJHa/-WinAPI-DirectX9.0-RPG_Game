#pragma once
#include<Windows.h>
#include<vector>
class Character;
class Sprite;
enum eStateType;
class State
{
public:
	State();
	~State();
protected:
	Character* _character;
	std::vector<Sprite*> _spriteList;
	eStateType _nextState;
public:
	virtual void Init(Character* character);
	virtual void DInit();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void Release();
	virtual void Reset();

	virtual void Start();
	virtual void Stop();
public:
	virtual void CreateSprite();
};