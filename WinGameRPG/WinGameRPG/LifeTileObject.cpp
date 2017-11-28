#include"LifeTileObject.h"
#include"GameSystem.h"
#include"Map.h"
#include"Stage.h"
#include"ComponentSystem.h"
LifeTileObject::LifeTileObject(int tileX, int tileY, LPCWSTR name, Sprite* sprite) :
	TileObject(name, sprite)
{
	_tileX = tileX;
	_tileY = tileY;
}

LifeTileObject::~LifeTileObject()
{

}
void LifeTileObject::Update(float deltaTime)
{
	TileObject::Update(deltaTime);
	Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
	int range = 1;
	//주변 캐릭터 마리 수를 세기
	int surroundedCharacter = 0;
	//FindComponentInRange 내 기능을 통하여 캐릭터 마리 수 가져올 것(자신을 제외한 탐색)
	Component* tileCharacter = NULL;

	int minX = _tileX - range;
	int minY = _tileY - range;
	int maxX = _tileX + range;
	int maxY = _tileY + range;
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
	for (int y = minY; y < maxY; y++)
	{
		for (int x = minX; x < maxX; x++)
		{
			if (x != _tileX || y != _tileY)
			{
				std::list<Component*> collisionList;
				if (false == map->GetTileCollisionList(x, y, collisionList))
				{
					//collisionList 순환
					for (std::list<Component*>::iterator itCollision = collisionList.begin();
						itCollision != collisionList.end();
						itCollision++)
					{
						Component* component = (*itCollision);
						if (component->IsLive())
						{
							switch (component->GetType())
							{
							case CT_PLAYER:
							case CT_NPC:
								surroundedCharacter++;
								break;
							default:
								break;
							}
						}
					}
				}
			}
			else
			{
				std::list<Component*> collisionList;
				if (false == map->GetTileCollisionList(x, y, collisionList))
				{
					//collisionList 순환
					for (std::list<Component*>::iterator itCollision = collisionList.begin();
						itCollision != collisionList.end();
						itCollision++)
					{
						Component* component = (*itCollision);
						if (component->IsLive())
						{
							switch (component->GetType())
							{
							case CT_PLAYER:
							case CT_NPC:
								tileCharacter = component;
								break;
							default:
								break;
							}
						}
					}
				}
			}
		}
	}
	if (3 == surroundedCharacter)
	{
		if (NULL == tileCharacter)
		{
			GameSystem::GetInstance()->GetStage()->CreateLifeNPC(_tileX, _tileY);
		}
	}
	else if (2 == surroundedCharacter)
	{
		//skip
	}
	else
	{
		//dead
		if (NULL != tileCharacter)
		{
			if (eComponentType::CT_PLAYER != tileCharacter->GetType())
			{
				GameSystem::GetInstance()->GetStage()->DestroyLifeNPC(_tileX, _tileY, tileCharacter);
			}
		}
	}

	wchar_t timeCheck[256];
	swprintf(timeCheck, L"deltaTime %f\n", deltaTime);
	OutputDebugString(timeCheck);
}