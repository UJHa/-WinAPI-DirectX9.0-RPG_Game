#include"MoveState.h"
#include"Character.h"
#include"Map.h"
#include"ComponentSystem.h"
MoveState::MoveState()
{
}

MoveState::~MoveState()
{
}
bool MoveState::IsMoving()
{
	return _isMoving;
}
void MoveState::Init(Character* character)
{
	_character = character;
	_isMoving = false;
	_movingDuration = 0.0f;
}
void MoveState::SetMoving(bool isMoving)
{
	_isMoving = isMoving;
}
float MoveState::GetMovingDuration()
{
	return _movingDuration;
}
void MoveState::Start()
{
	if (true == _isMoving)
		return;
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");

	int newTileX = _character->GetTileX();
	int newTileY = _character->GetTileY();
	switch (_character->GetDirection())
	{
	case eDirection::LEFT:
		newTileX--;
		break;
	case eDirection::RIGHT:
		newTileX++;
		break;
	case eDirection::UP:
		newTileY--;
		break;
	case eDirection::DOWN:
		newTileY++;
		break;
	}

	std::list<Component*> collisionList;
	bool canMove = map->GetTileCollisionList(newTileX, newTileY, collisionList);
	if (false == canMove)
	{
		_character->Collision(collisionList);
	}
	else
	{
		_character->MoveStart(newTileX, newTileY);
	}
	_isMoving = true;
}
void MoveState::Stop()
{
	_movingDuration = 0.0f;
	_isMoving = false;
}
void MoveState::Update(float deltaTime)
{
	if (false == _character->IsLive())
		return;
	if (false == _isMoving)
		return;
	_character->UpdateMove(deltaTime);
}
void MoveState::UpdateMove(float deltaTime)
{
	_movingDuration += deltaTime;
}