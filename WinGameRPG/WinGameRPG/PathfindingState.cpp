#include "PathfindingState.h"
#include "GameSystem.h"
#include "Character.h"
#include "Map.h"
#include "Stage.h"
#include "GlobalType.h"
PathfindingState::PathfindingState()
{
	_updateState = eUpdateState::PATHFINDING;
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

	switch (_updateState)
	{
	case eUpdateState::PATHFINDING:
		UpdatePathFinding();
		break;
	case eUpdateState::BUILD_PATH:
		UpdateBuildPath();
		break;
	default:
		break;
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
	sPathCommand newCommand;
	newCommand.heuristic = 0.0f;
	newCommand.tileCell = startTileCell;
	_pathFindingTileQueue.push(newCommand);
	_updateState = eUpdateState::PATHFINDING;
}
void PathfindingState::Stop()
{
	State::Stop();
	while (0 != _pathFindingTileQueue.size())
		_pathFindingTileQueue.pop();
}
void PathfindingState::UpdatePathFinding()
{
	if (0 != _pathFindingTileQueue.size())
	{
		//TileCell* tileCell = _pathFindingTileQueue.top();
		sPathCommand command = _pathFindingTileQueue.top();

		_pathFindingTileQueue.pop();
			
		if (false == command.tileCell->IsPathFindingMark())
		{
			command.tileCell->PathFinded();
			if (command.tileCell->GetTileX() == _targetTileCell->GetTileX() &&
				command.tileCell->GetTileY() == _targetTileCell->GetTileY())
			{
				std::list<Component*> comList = command.tileCell->GetComponentList();
				for (std::list<Component*>::iterator it = comList.begin(); it != comList.end(); it++)
				{
					Character* monster = (Character*)(*it);

					if (command.tileCell->GetTileX() < command.tileCell->GetPrevPathFindingCell()->GetTileX())
					{
						monster->SetDirection(eDirection::RIGHT);
					}
					else if (command.tileCell->GetTileX() > command.tileCell->GetPrevPathFindingCell()->GetTileX())
					{
						monster->SetDirection(eDirection::LEFT);
					}
					else if (command.tileCell->GetTileY() < command.tileCell->GetPrevPathFindingCell()->GetTileY())
					{
						monster->SetDirection(eDirection::DOWN);
					}
					else if (command.tileCell->GetTileY() > command.tileCell->GetPrevPathFindingCell()->GetTileY())
					{
						monster->SetDirection(eDirection::UP);
					}
				}
				OutputDebugString(L"Find Goal\n");
				_updateState = eUpdateState::BUILD_PATH;
				_reverseTileCell = _targetTileCell;
				return;
			}
			for (int direction = 0; direction < eDirection::NONE; direction++)
			{
				TilePosition currentTilePos;
				currentTilePos.x = command.tileCell->GetTileX();
				currentTilePos.y = command.tileCell->GetTileY();
				TilePosition nextTilePos = GetNextTilePosition(currentTilePos, (eDirection)direction);

				Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
				TileCell* nextTileCell = map->GetTileCell(nextTilePos);
				// (이동 가능 타일 && 검사한적 없는 타일일 때) 이거나  (다음 타일셀이 타겟 타일셀일때)
				if ((true == map->CanMoveTileMap(nextTilePos) && false == nextTileCell->IsPathFindingMark())
					|| (nextTileCell->GetTileX() == _targetTileCell->GetTileX() && nextTileCell->GetTileY() == _targetTileCell->GetTileY()))
				{
					float distanceFromStart = command.tileCell->GetDistanceFromStart() + command.tileCell->GetDistanceWeight();
					//float heuristic = distanceFromStart;
					float heuristic = CalcAStarHeuristic(distanceFromStart, nextTileCell, _targetTileCell);

					//이전 타일 셀 설정 안되있을 때(첫 설정일때)
					if (NULL == nextTileCell->GetPrevPathFindingCell())
					{
						nextTileCell->SetDistanceFromStart(distanceFromStart);
						nextTileCell->SetHeuristic(heuristic);
						nextTileCell->SetPrevPathFindingCell(command.tileCell);
						//_pathFindingTileQueue.push(nextTileCell);

						sPathCommand newCommand;
						newCommand.heuristic = heuristic;
						newCommand.tileCell = nextTileCell;
						_pathFindingTileQueue.push(newCommand);
					}
					else
					{
						if (distanceFromStart < nextTileCell->GetDistanceFromStart())
						{
							nextTileCell->SetDistanceFromStart(distanceFromStart);
							nextTileCell->SetPrevPathFindingCell(command.tileCell);
							//_pathFindingTileQueue.push(nextTileCell);

							sPathCommand newCommand;
							newCommand.heuristic = CalcAStarHeuristic(distanceFromStart, nextTileCell, _targetTileCell);
							newCommand.tileCell = nextTileCell;
							_pathFindingTileQueue.push(newCommand);
						}
					}
				}
			}
		}
	}
}
void PathfindingState::UpdateBuildPath()
{
	if (NULL != _reverseTileCell)
	{
		_character->PushPathTileCellStack(_reverseTileCell);
		_reverseTileCell = _reverseTileCell->GetPrevPathFindingCell();
	}
	else
	{
		_nextState = eStateType::ET_MOVE;
	}
}
float PathfindingState::CalcSimpleHeuristic(TileCell* tileCell, TileCell* nextTileCell, TileCell* targetTileCell)
{
	float heuristic = 0.0f;

	int diffFromCurrent = 0;
	int diffFromNext = 0;
	// x축 : 발견적 값 갱신
	{
		diffFromCurrent = tileCell->GetTileX() - targetTileCell->GetTileX();
		if (diffFromCurrent < 0)
			diffFromCurrent = -diffFromCurrent;

		diffFromNext = nextTileCell->GetTileX() - targetTileCell->GetTileX();
		if (diffFromNext < 0)
			diffFromNext = -diffFromNext;

		if (diffFromNext < diffFromCurrent)
		{
			heuristic -= 1.0f;
		}
		else if (diffFromNext > diffFromCurrent)
		{
			heuristic += 1.0f;
		}
	}
	// y축 : 발견적 값 누적 갱신
	{
		diffFromCurrent = tileCell->GetTileY() - targetTileCell->GetTileY();
		if (diffFromCurrent < 0)
			diffFromCurrent = -diffFromCurrent;

		diffFromNext = nextTileCell->GetTileY() - targetTileCell->GetTileY();
		if (diffFromNext < 0)
			diffFromNext = -diffFromNext;

		if (diffFromNext < diffFromCurrent)
		{
			heuristic -= 1.0f;
		}
		else if (diffFromNext > diffFromCurrent)
		{
			heuristic += 1.0f;
		}
	}
	{
		diffFromCurrent = tileCell->GetDistanceWeight();

		diffFromNext = nextTileCell->GetDistanceWeight();

		if (diffFromNext < diffFromCurrent)
		{
			heuristic += 1.0f;
		}
		else if (diffFromNext > diffFromCurrent)
		{
			heuristic -= 1.0f;
		}
	}
	return heuristic;
}
float PathfindingState::CalcComplexHeuristic(TileCell* nextTileCell, TileCell* targetTileCell)
{
	int distanceW = nextTileCell->GetTileX() - targetTileCell->GetTileX();
	int distanceH = nextTileCell->GetTileY() - targetTileCell->GetTileY();
	distanceW *= distanceW;
	distanceH *= distanceH;
	float distance = distanceW + distanceH;
	return distance;
}
float PathfindingState::CalcAStarHeuristic(float distanceFromStart, TileCell* nextTileCell, TileCell* targetTileCell)
{
	return distanceFromStart + CalcComplexHeuristic(nextTileCell, targetTileCell);
}