#include"NPC.h"
#include"Map.h"
#include"ComponentSystem.h"
#include"sComponentMsgParam.h"
#include"MoveState.h"
#include"GameSystem.h"
#include"Stage.h"
NPC::NPC(wstring name, wstring scriptName, wstring pngName) : Character(name, scriptName, pngName)
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
	//Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
	Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
	std::vector<eComponentType> compareTypeList;
	compareTypeList.push_back(eComponentType::CT_MONSTER);
	Component *findEnemy = ComponentSystem::GetInstance()->FindComponentInRange(map, this, 2, compareTypeList);
	if (NULL != findEnemy)
	{
		//_moveTime = 0.3f;
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
				_state->NextState(eStateType::ET_MOVE);
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