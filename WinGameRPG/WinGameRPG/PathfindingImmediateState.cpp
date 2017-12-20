#include "PathfindingImmediateState.h"
PathfindingImmediateState::PathfindingImmediateState()
{
}

PathfindingImmediateState::~PathfindingImmediateState()
{
}
void PathfindingImmediateState::Start()
{
	PathfindingState::Start();

	while (0 != _pathFindingTileQueue.size())
	{
		if (eUpdateState::BUILD_PATH == _updateState)
			break;
		UpdatePathFinding();
	}

	while (NULL != _reverseTileCell)
	{
		UpdateBuildPath();
	}
}