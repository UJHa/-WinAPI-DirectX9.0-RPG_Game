#pragma once
#include<map>
#include<vector>
#include<list>
#include<string>
#include"Component.h"
using namespace std;
enum eDirection {
	LEFT, RIGHT, UP, DOWN, NONE,
};
enum eStateType
{
	ET_IDLE, ET_MOVE, ET_ATTACK, ET_DEFENSE, ET_DEAD, ET_NONE,
};
class Sprite;
class State;
class Font;
class Character : public Component
{
protected:
	float _x;
	float _y;
	wstring _scrpitName;
	wstring _pngName;

	int _hp;
private:
	//std::vector<Sprite*> _spriteList;
	float _deltaX;
	float _deltaY;
public:
	Character(wstring name, wstring scriptName, wstring pngName);
	virtual ~Character();

	void Init();
	void Init(int tileX, int tileY);
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
public:
	virtual void InitState();
	void ReplaceState(eStateType changeType, State* replaceState);
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
	float GetCoolTime() { return _attackCoolTimeDuration; }
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
	void IncreaseHP(int increaseHpPoint);
	void DecreaseHP(int decreaseHpPoint);
	//message
public:
	void ReceiveMessage(const sComponentMsgParam msgParam);
	//UI
protected:
	Font* _font;
public:
	virtual void UpdateText();
};