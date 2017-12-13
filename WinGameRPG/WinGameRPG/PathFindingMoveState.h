#pragma once
#include"State.h"
#include<stack>
using namespace std;
class Character;
class TileCell;
class PathFindingMoveState : public State
{
public:
	PathFindingMoveState();
	~PathFindingMoveState();
private:
	float _movingDuration;
	stack<TileCell*> _pathTileCellStack;
public:
	void Init(Character* character);
	void Update(float deltaTime);

	void Start();
	void Stop();
};