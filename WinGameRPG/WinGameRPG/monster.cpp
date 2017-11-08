#include"Monster.h"
Monster::Monster(LPCWSTR name, LPCWSTR scriptName, LPCWSTR pngName) : Character(name, scriptName, pngName)
{
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
		Component* findEnemy = NULL;
		{
			component->GetType() == eComponentType::CT_NPC or eComponentType::CT_PLAYER
				findEnemy = component;
			break;
		}
		if (NULL != findEnemy)
		{
			//추격
			eDirection direction = eDirection::NONE;
			MoveStart(direction);
		}
		else
		{
			Character::UpdateAI();
		}
	}
}