#pragma once
#include<map>
#include<vector>
#include<list>
#include<string>
#include"Component.h"
enum eDirection {
	LEFT, RIGHT, UP, DOWN, NONE,
};
enum eStateType
{
	ET_IDLE, ET_MOVE, ET_ATTACK
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

	int _hp;
private:
	//std::vector<Sprite*> _spriteList;
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
	std::wstring GetScriptFileName() { return _scrpitName; }
	std::wstring GetTextureFileName() { return _pngName; }
	float GetX() { return _x; }
	float GetY() { return _y; }
	//AI
public:
	virtual void UpdateAI();
	void ChangeState(eStateType stateType);
	//State
protected:
	State* _state;
	std::map<eStateType, State*> _stateMap;
	//Move
protected:
	float _moveTime;
	bool _isMoving;

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
	//Attack
protected:
	Component* _targetComponent;
	int _attackPoint;
public:
	int GetAttackPoint() { return _attackPoint; }
	Component* GetTarget() { return _targetComponent; }
	void ResetTarget() { _targetComponent = NULL; }
public:
	virtual void Collision(std::list<Component*>& collisionList);
	void ReceiveMessage(const sComponentMsgParam msgParam);
};