#pragma once
#include<Windows.h>
#include<vector>
#include<list>
#include<string>
#include"Component.h"
enum eDirection {
	LEFT, RIGHT, UP, DOWN, NONE,
};
enum eStateType
{
	ET_IDLE, ET_MOVE,
};
class Sprite;
class State;
class Character : public Component
{
protected:
	float _x;
	float _y;
	std::wstring _scrpitName;
	std::wstring _pngName;

	int _attackPoint;
	int _hp;
private:
	std::vector<Sprite*> _spriteList;

	float _deltaX;
	float _deltaY;
public:
	Character(LPCWSTR name, LPCWSTR scriptName, LPCWSTR pngName);
	virtual ~Character();

	void Init();
	void DInit();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();
	// transform
public:
	virtual void MoveDeltaPosition(float deltaX, float deltaY);
	void SetPosition(float posX, float posY);
	//AI
public:
	virtual void UpdateAI();
	void ChangeState(eStateType stateType);
	//Move
protected:
	float _moveTime;
	bool _isMoving;
	//float _movingDuration;
	State* _state;

	eDirection _currentDirection;
	float _targetX;
	float _targetY;
public:
	void InitMove();
	void MoveStart(int newTileX, int newTileY);
	void MoveStop();
	void Moving(float deltaTime);
	float GetMoveTime() { return _moveTime; }
	eDirection GetDirection() { return _currentDirection; }
	bool IsMoving() { return _isMoving; }

	virtual void Collision(std::list<Component*>& collisionList);
	void ReceiveMessage(const sComponentMsgParam msgParam);
};