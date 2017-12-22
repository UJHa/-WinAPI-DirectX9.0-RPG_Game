#include "RangeAttackState.h"
#include "Character.h"
#include "GameSystem.h"
#include "Map.h"
#include "Stage.h"
#include "sComponentMsgParam.h"
#include "ComponentSystem.h"
#include "Component.h"
RangeAttackState::RangeAttackState()
{
	_nowState = eStateType::ET_RANGE_ATTACK;
	_range = 10;
}
RangeAttackState::~RangeAttackState()
{
}
void RangeAttackState::Update(float deltaTime)
{
	State::Update(deltaTime);
	AttackEffectWave(_waveIndex);
	AttackEffectWave(_waveIndex + 1);
	AttackEffectWave(_waveIndex + 2);
	RemoveEffectWave(_waveIndex - 1);
	_waveIndex++;
	if (_waveIndex == _range)
		_nextState = eStateType::ET_IDLE;
}
void RangeAttackState::Start()
{
	State::Start();
	_waveIndex = 0;
	_waveTileCellList.clear();
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
	_attackTileQueue.push(startTileCell);

	SetWaveAttack(_range);
}
void RangeAttackState::Stop()
{
	State::Stop();
	while (0 != _attackTileQueue.size())
		_attackTileQueue.pop();
}
void RangeAttackState::SetWaveAttack(int range)
{
	while (0 != _attackTileQueue.size())
	{
		TileCell* tileCell = _attackTileQueue.front();
		_attackTileQueue.pop();

		if (false == tileCell->IsPathFindingMark())
		{
			tileCell->PathFinded();
			float distanceFromStart;
			for (int direction = 0; direction < eDirection::NONE; direction++)
			{
				TilePosition currentTilePos;
				currentTilePos.x = tileCell->GetTileX();
				currentTilePos.y = tileCell->GetTileY();
				TilePosition nextTilePos = GetNextTilePosition(currentTilePos, (eDirection)direction);

				Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
				TileCell* currentTileCell = map->GetTileCell(currentTilePos);
				TileCell* nextTileCell = map->GetTileCell(nextTilePos);
				// 검사한적 없는 타일일 때
				if (false == nextTileCell->IsPathFindingMark())
				{
					distanceFromStart = currentTileCell->GetDistanceFromStart() + 1.0f;
					if (range == (int)distanceFromStart)
						break;
					nextTileCell->SetDistanceFromStart(distanceFromStart);
					nextTileCell->SetPrevPathFindingCell(tileCell);
					_attackTileQueue.push(nextTileCell);
					_waveTileCellList[(int)distanceFromStart].push_back(nextTileCell);
				}
			}
		}
	}
}
void RangeAttackState::AttackEffectWave(int waveIndex)
{
	if (waveIndex == _range)
		return;
	for (std::vector<TileCell*>::iterator it = _waveTileCellList[waveIndex].begin();
		it != _waveTileCellList[waveIndex].end(); it++)
	{
		GameSystem::GetInstance()->GetStage()->CreateEffect(*it);
		if (false == (*it)->CanMove())
		{
			std::list<Component*> collisionList;
			(*it)->GetCollisionList(collisionList);
			for (std::list<Component*>::iterator itCollision = collisionList.begin(); itCollision != collisionList.end(); itCollision++)
			{
				sComponentMsgParam msgParam;
				msgParam.sender = (Component*)_character;
				msgParam.attackPoint = 100;
				msgParam.receiver = (*itCollision);
				msgParam.message = L"Attack";
				ComponentSystem::GetInstance()->SendMsg(msgParam);
			}
		}
	}
}
void RangeAttackState::RemoveEffectWave(int waveIndex)
{
	if (waveIndex < 1)
		return;
	for (std::vector<TileCell*>::iterator it = _waveTileCellList[waveIndex].begin();
		it != _waveTileCellList[waveIndex].end(); it++)
	{
		GameSystem::GetInstance()->GetStage()->RemoveEffect(*it);
	}
}