#include"Monster.h"
#include"ComponentSystem.h"
#include"Map.h"
#include "sComponentMsgParam.h"
#include "MoveState.h"
Monster::Monster(LPCWSTR name, LPCWSTR scriptName, LPCWSTR pngName) : Character(name, scriptName, pngName)
{
	_componentType = eComponentType::CT_MONSTER;
	int speed = (rand() % 1500) + 200;
	_moveTime = (float)speed / 1000.0f;
}

Monster::~Monster()
{
}
void Monster::UpdateAI()
{
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
	std::vector<eComponentType> compareTypeList;
	compareTypeList.push_back(eComponentType::CT_NPC);
	compareTypeList.push_back(eComponentType::CT_PLAYER);
	Component* findEnemy = ComponentSystem::GetInstance()->FindComponentInRange(this, 4, compareTypeList);
	if (NULL != findEnemy)
	{
		//_moveTime = 0.5f;
		//Ãß°Ý
		eDirection direction = eDirection::NONE;
		if (findEnemy->GetTileX() < _tileX)
			direction = eDirection::LEFT;
		if (findEnemy->GetTileX() > _tileX)
			direction = eDirection::RIGHT;
		if (findEnemy->GetTileY() < _tileY)
			direction = eDirection::UP;
		if (findEnemy->GetTileY() > _tileY)
			direction = eDirection::DOWN;
		_currentDirection = direction;
		ChangeState(ET_MOVE);
	}
	else
	{
		_currentDirection = (eDirection)(rand() % 4);
		Character::UpdateAI();
	}
}
Component* Monster::Collision(std::list<Component*>& collisionList)
{
	for (std::list<Component*>::iterator it = collisionList.begin(); it != collisionList.end(); it++)
	{
		if ((*it)->GetType() == eComponentType::CT_NPC ||
			(*it)->GetType() == eComponentType::CT_PLAYER)
		{
			/*sComponentMsgParam msgParam;
			msgParam.sender = this;
			msgParam.attackPoint = _attackPoint;
			msgParam.receiver = (*it);
			msgParam.message = L"Attack";
			ComponentSystem::GetInstance()->SendMsg(msgParam);*/
			_targetComponent = (*it);
			ChangeState(eStateType::ET_ATTACK);
			return (*it);
		}
	}
	//ChangeState(eStateType::ET_IDLE);
	return NULL;
}