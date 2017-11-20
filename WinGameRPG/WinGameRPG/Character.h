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
	ET_IDLE, ET_MOVE, ET_ATTACK, ET_DEFENSE, ET_DEAD, ET_NONE,
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
	float _attackCoolTimeDuration;
	float  _attackCoolTime;
public:
	void UpdateAttackCoolTime(float deltaTime);
	bool IsAttackCoolTime();
	void ResetAttackCoolTime();
	float GetCoolTime() {return _attackCoolTimeDuration; }
	int GetAttackPoint() { return _attackPoint; }
	Component* GetTarget() { return _targetComponent; }
	void SetTarget(Component* target) { _targetComponent = target; }
	void ResetTarget() { _targetComponent = NULL; }
	//defense
protected:
	int _attackedPoint;
public:
	int GetRecevieAttackPoint() { return _attackedPoint; }
public:
	virtual Component* Collision(std::list<Component*>& collisionList);
	//common
public:
	void DecreaseHP(int decreaseHPpont);
	//message
public:
	void ReceiveMessage(const sComponentMsgParam msgParam);
};