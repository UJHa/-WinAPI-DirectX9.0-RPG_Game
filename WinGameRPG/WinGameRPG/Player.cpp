#include"Player.h"
#include"GameSystem.h"
#include"ComponentSystem.h"
#include"Map.h"
#include"MoveState.h"
#include"Stage.h"
Player::Player(LPCWSTR name, LPCWSTR scriptName, LPCWSTR pngName) : Character(name, scriptName, pngName)
{
	_moveTime = 0.1f;
	_componentType = eComponentType::CT_PLAYER;
}

Player::~Player()
{
}
void Player::UpdateAI()
{
	eDirection direction = eDirection::NONE;
	if (GameSystem::GetInstance()->IsKeyDown(VK_UP))
		direction = eDirection::UP;
	if (GameSystem::GetInstance()->IsKeyDown(VK_DOWN))
		direction = eDirection::DOWN;
	if (GameSystem::GetInstance()->IsKeyDown(VK_LEFT))
		direction = eDirection::LEFT;
	if (GameSystem::GetInstance()->IsKeyDown(VK_RIGHT))
		direction = eDirection::RIGHT;

	if (eDirection::NONE != direction)
	{
		_currentDirection = direction;
		_state->NextState(eStateType::ET_MOVE);
	}
	if (GameSystem::GetInstance()->IsKeyDown(VK_SPACE))
	{
		//Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
		Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
		std::list<Component*> componentList = map->GetTileComponentList(_tileX,_tileY);
		for (std::list<Component*>::iterator it = componentList.begin(); it != componentList.end(); it++)
		{
			Component* component = (*it);
			if (eComponentType::CT_ITEM == component->GetType())
			{
				sComponentMsgParam msgParam;
				msgParam.sender = (Component*)this;
				msgParam.receiver = component;
				msgParam.message = L"Use";
				ComponentSystem::GetInstance()->SendMsg(msgParam);
			}
		}
	}
}
Component* Player::Collision(std::list<Component*>& collisionList)
{
	for (std::list<Component*>::iterator it = collisionList.begin(); it != collisionList.end(); it++)
	{
		if ((*it)->GetType() == eComponentType::CT_NPC ||
			(*it)->GetType() == eComponentType::CT_MONSTER)
		{
			_targetComponent = (*it);
			_state->NextState(eStateType::ET_ATTACK);
			return (*it);
		}
	}
	return NULL;
}