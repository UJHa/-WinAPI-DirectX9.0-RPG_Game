#pragma once
#include<Windows.h>
class Component
{
protected:
	LPCWSTR _name;
	bool _canMove;
public:
	Component() { _canMove = true; }
	Component(LPCWSTR name);
	virtual ~Component();

	virtual void Init() = 0;
	virtual void DInit() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
	virtual void Reset() = 0;

	virtual void MoveDeltaPosition(float deltaX, float deltaY) {}
	virtual void SetPosition(float posX, float posY) {}
	void SetCanMove(bool canMove) { _canMove = canMove; }
	bool CanMove() { return _canMove; }
};