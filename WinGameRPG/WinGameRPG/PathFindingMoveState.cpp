#include"PathFindingMoveState.h"
#include"Character.h"
#include"Map.h"
#include"ComponentSystem.h"
#include"GameSystem.h"
#include"Stage.h"
#include "GlobalType.h"
#include "TileCell.h"
PathFindingMoveState::PathFindingMoveState()
{
	_nowState = eStateType::ET_MOVE;
}

PathFindingMoveState::~PathFindingMoveState()
{
}
void PathFindingMoveState::Init(Character* character)
{
	State::Init(character);
	_nextState = eStateType::ET_NONE;
	_movingDuration = 0.0f;
}
void PathFindingMoveState::Update(float deltaTime)
{
	State::Update(deltaTime);
	if (false == _character->IsLive())
		return;
	if (_character->GetMoveTime() <= _movingDuration)
	{
		_movingDuration = 0.0f;
		if (0 != _pathTileCellStack.size())
		{
			TileCell* tileCell = _pathTileCellStack.top();
			_pathTileCellStack.pop();

			//캐릭터가 방향 바꿔가며 이동, 너무 빠르게 가는것 고치기
			TilePosition to;
			to.x = tileCell->GetTileX();
			to.y = tileCell->GetTileY();

			TilePosition from;
			from.x = _character->GetTileX();
			from.y = _character->GetTileY();
			eDirection direction = GetDirection(to, from);
			if (eDirection::NONE != direction)
			{
				_character->SetDirection(direction);
			}
			Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
			std::list<Component*> collisionList;
			bool canMove = map->GetTileCollisionList(tileCell->GetTileX(), tileCell->GetTileY(), collisionList);
			if (!canMove)
			{
				_nextState = eStateType::ET_IDLE;
				return;
			}
			_character->MoveStart(tileCell->GetTileX(), tileCell->GetTileY());
			_character->MoveStop();
		}
		else
		{
			_nextState = eStateType::ET_IDLE;
		}
	}
	else
	{
		_movingDuration += deltaTime;
	}
}
void PathFindingMoveState::Start()
{
	State::Start();
	
	_movingDuration = 0.0f;	//add code
	_nextState = eStateType::ET_NONE;
	_pathTileCellStack = _character->GetPathTileCellStack();
	if (0 != _pathTileCellStack.size())
	{
		_pathTileCellStack.pop();
	}
}
void PathFindingMoveState::Stop()
{
	State::Stop();
	Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
	map->ViewerScroll(_character, 0.0f, 0.0f);
	_character->ClearPathTileCellStack();
}