#include "PathfindingState.h"
#include "GameSystem.h"
#include "Character.h"
#include "Map.h"
#include "Stage.h"
#include "TileCell.h"
#include "GlobalType.h"
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
				std::list<Component*> comList = tileCell->GetComponentList();
				for (std::list<Component*>::iterator it = comList.begin(); it != comList.end(); it++)
				{
					Character* monster = (Character*)(*it);

					if (tileCell->GetTileX() < tileCell->GetPrevPathFindingCell()->GetTileX())
					{
						monster->SetDirection(eDirection::RIGHT);
					}
					else if (tileCell->GetTileX() > tileCell->GetPrevPathFindingCell()->GetTileX())
					{
						monster->SetDirection(eDirection::LEFT);
					}
					else if (tileCell->GetTileY() < tileCell->GetPrevPathFindingCell()->GetTileY())
					{
						monster->SetDirection(eDirection::UP);
					}
					else if (tileCell->GetTileY() > tileCell->GetPrevPathFindingCell()->GetTileY())
					{
						monster->SetDirection(eDirection::DOWN);
					}
				}
				OutputDebugString(L"Find Goal\n");
				_nextState = eStateType::ET_IDLE;
				return;
			}
			for (int direction = 0; direction < eDirection::NONE; direction++)
			{
				TilePosition currentTilePos;
				currentTilePos.x = tileCell->GetTileX();
				currentTilePos.y = tileCell->GetTileY();
				TilePosition nextTilePos = GetNextTilePosition(currentTilePos, (eDirection)direction);

				Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
				TileCell* nextTileCell = map->GetTileCell(nextTilePos);
				wchar_t msg[256];
				swprintf(msg, L"pathFindingState %d %d\n", nextTileCell->GetTileX(), nextTileCell->GetTileY());
				OutputDebugString(msg);
				if ((true == map->CanMoveTileMap(nextTilePos) && false == nextTileCell->IsPathFindingMark())
					|| (nextTileCell->GetTileX() == _targetTileCell->GetTileX() && nextTileCell->GetTileY() == _targetTileCell->GetTileY()))
				{
					if (NULL == nextTileCell->GetPrevPathFindingCell())
					{
						nextTileCell->SetPrevPathFindingCell(tileCell);
						_pathFindingTileQueue.push(nextTileCell);
						
						//몬스터 플레이어 제외한 Cell npc 생성
						if (!((nextTileCell->GetTileX() == _targetTileCell->GetTileX())
							&& (nextTileCell->GetTileY() == _targetTileCell->GetTileY()))
							&&
							!(nextTileCell->GetTileX() == _character->GetTileX()
								&& nextTileCell->GetTileY() == _character->GetTileY())
							)
						{
							GameSystem::GetInstance()->GetStage()->CreatePathfinderNPC(nextTileCell);
							wchar_t msg[256];
							swprintf(msg, L"pathFindingState next %d %d\n", nextTileCell->GetTileX(), nextTileCell->GetTileY());
							OutputDebugString(msg);
						}
					}
				}
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
	while (0 != _pathFindingTileQueue.size())
		_pathFindingTileQueue.pop();
}