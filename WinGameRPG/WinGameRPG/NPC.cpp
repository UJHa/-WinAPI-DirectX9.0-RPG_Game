#include"NPC.h"
#include"Map.h"
#include"ComponentSystem.h"
#include"sComponentMsgParam.h"
#include"MoveState.h"
NPC::NPC(LPCWSTR name, LPCWSTR scriptName, LPCWSTR pngName) : Character(name, scriptName, pngName)
{
	_componentType = eComponentType::CT_NPC;
	int speed = (rand() % 1500) + 400;
	_moveTime = (float)speed / 1000.0f;
}

NPC::~NPC()
{
}
void NPC::UpdateAI()
{
	if (false == _isLive)
		return;
	if (false == _state->IsMoving())
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
		std::vector<eComponentType> compareTypeList;
		compareTypeList.push_back(eComponentType::CT_MONSTER);
		Component *findEnemy = ComponentSystem::GetInstance()->FindComponentInRange(this, 2, compareTypeList);
		if (NULL != findEnemy)
		{
			//_moveTime = 0.3f;
			//추격
			eDirection direction = eDirection::NONE;
			for (int findDir = 0; findDir < 4; findDir++)
			{
				int newTileX = _tileX;
				int newTileY = _tileY;
				switch (findDir)
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
				if (map->CanMoveTileMap(newTileX, newTileY))
				{
					direction = (eDirection)findDir;
					_currentDirection = direction;
					_state->Start();
					break;
				}
			}
		}
		else
		{
			//_moveTime = 1.0f;
			Character::UpdateAI();
		}
	}
}