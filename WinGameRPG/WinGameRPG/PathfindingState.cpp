#include "PathfindingState.h"
#include "GameSystem.h"
#include "Character.h"
#include "Map.h"
#include "Stage.h"
#include "TileCell.h"
PathfindingState::PathfindingState()
{
}

PathfindingState::~PathfindingState()
{
}
void PathfindingState::Init(Character* character)
{
	State::Init(character);
}
void PathfindingState::Update(float deltaTime)
{
	State::Update(deltaTime);
	if (0 != _pathFindingTileQueue.size())
	{
		TileCell* tileCell = _pathFindingTileQueue.front();
		_pathFindingTileQueue.pop();
		if (false == tileCell->IsPathFindingMark())
		{
			tileCell->PathFinded();
			if (tileCell->GetTileX() == _targetTileCell->GetTileX() &&
				tileCell->GetTileY() == _targetTileCell->GetTileY())
			{
				_nextState = eStateType::ET_IDLE;
				return;
			}
			
		}
	}
}
void PathfindingState::Start()
{
	State::Start();
	_targetTileCell = _character->GetTargetCell();

	Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
	int height = map->GetHeight();
	int width = map->GetWidth();

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			TileCell* tileCell = map->GetTileCell(x, y);
			tileCell->InitPathfinding();
		}
	}
	TileCell* startTileCell = map->GetTileCell(_character->GetTileX(), _character->GetTileY());
	_pathFindingTileQueue.push(startTileCell);
}
void PathfindingState::Stop()
{
	State::Stop();
}