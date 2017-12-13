#pragma once
#include<queue>
#include "State.h"
class TileCell;
class PathfindingState : public State
{
public:
	PathfindingState();
	~PathfindingState();
public:
	void Init(Character* character);
	void Update(float deltaTime);

	void Start();
	void Stop();
	//path finding
public:
	enum eUpdateState
	{
		PATHFINDING,
		BUILD_PATH,
	};
private:
	std::queue<TileCell*> _pathFindingTileQueue;
	TileCell* _targetTileCell;
	TileCell* _reverseTileCell;
	eUpdateState _updateState;
public:
	void UpdatePathFinding();
	void UpdateBuildPath();
};