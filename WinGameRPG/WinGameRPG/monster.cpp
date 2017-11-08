#include"Monster.h"
#include"ComponentSystem.h"
#include"Map.h"
Monster::Monster(LPCWSTR name, LPCWSTR scriptName, LPCWSTR pngName) : Character(name, scriptName, pngName)
{
	_componentType = eComponentType::CT_MONSTER;
}

Monster::~Monster()
{
}
void Monster::UpdateAI()
{
	if (false == _isMoving)
	{
		/*
		나를 기준으로 몇칸의 타일 검사할지 결정
		검사하는 타일 범위 구한다
		범위내 모든 타일을 검사
		npc or player 있으면
		적을 찾았다
		못찾으면 
		평소 rand 움직임
		*/
		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
		Component* findEnemy = NULL;
		int minX = _tileX - 4;
		int minY = _tileY - 4;
		int maxX = _tileX + 4;
		int maxY = _tileY + 4;
		if (minX < 0) {
			minX = 0;
		}
		if (minY < 0) {
			minY = 0;
		}
		if (map->GetWidth() <= maxX) {
			maxX = map->GetWidth() - 1;
		}
		if (map->GetHeight() <= maxY) {
			maxY = map->GetHeight() - 1;
		}
		{
			for (int y = minY; y <= maxY; y++)
			{
				for (int x = minX; x <= maxX; x++)
				{
					std::list<Component*> collisionList;
					bool canMove = map->GetTileCollisionList(x, y, collisionList);
					if (false == canMove)
					{
						//collisionList 순환
						for (std::list<Component*>::iterator it = collisionList.begin(); it != collisionList.end(); it++)
						{
							if ((*it)->GetType() == eComponentType::CT_NPC || (*it)->GetType() == eComponentType::CT_PLAYER)
							{
								findEnemy = (*it);
							}
						}
					}
				}
			}
		}
		if (NULL != findEnemy)
		{
			_moveTime = 0.05f;
			//추격
			eDirection direction = eDirection::NONE;
			int distanceX = _tileX - findEnemy->GetTileX();
			int distanceY = _tileY - findEnemy->GetTileY();
			/*if (distanceX < 0)
			{
				distanceX = -distanceX;
			}
			if (distanceY < 0)
			{
				distanceY = -distanceY;
			}*/
			int randXY = rand() % 2;
			if (randXY)
			{
				distanceY = _tileY - findEnemy->GetTileY();
				if (distanceY < 0)
					direction = eDirection::DOWN;
				else
					direction = eDirection::UP;
			}
			else
			{
				distanceX = _tileX - findEnemy->GetTileX();
				if (distanceX < 0)
					direction = eDirection::RIGHT;
				else
					direction = eDirection::LEFT;
			}
			MoveStart(direction);
		}
		else
		{
			_moveTime = 1.0f;
			Character::UpdateAI();
		}
	}
}