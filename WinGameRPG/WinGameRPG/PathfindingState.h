#pragma once
#include<queue>
#include "State.h"
#include "TileCell.h"
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
	typedef struct _sPathCommand
	{
		float heuristic;
		TileCell* tileCell;
	}sPathCommand;

	struct compare
	{
		bool operator()(sPathCommand& a, sPathCommand& b)
		{
			return a.heuristic > b.heuristic;
		}

	};
protected:
	std::priority_queue<sPathCommand, std::vector<sPathCommand>, compare> _pathFindingTileQueue;
	TileCell* _targetTileCell;
	TileCell* _reverseTileCell;
	eUpdateState _updateState;
public:
	void UpdatePathFinding();
	void UpdateBuildPath();

	float CalcSimpleHeuristic(TileCell* tileCell, TileCell* nextTileCell,TileCell* targetTileCell);
	float CalcComplexHeuristic(TileCell* nextTileCell, TileCell* targetTileCell);
	float CalcAStarHeuristic(float distanceFromStart, TileCell* nextTileCell, TileCell* targetTileCell);
};