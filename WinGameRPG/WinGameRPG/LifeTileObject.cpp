#include"LifeTileObject.h"
#include"GameSystem.h"
#include"Map.h"
#include"Stage.h"
#include"ComponentSystem.h"
LifeTileObject::LifeTileObject(LPCWSTR name, Sprite* sprite) :
	TileObject(name,sprite)
{
}

LifeTileObject::~LifeTileObject()
{

}
void LifeTileObject::Update(float deltaTime)
{
	TileObject::Update(deltaTime);
	Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
	//주변 캐릭터 마리 수를 세기
	std::vector<eComponentType> compareTypeList;
	//FindComponentInRange 내 기능을 통하여 캐릭터 마리 수 가져올 것(자신을 제외한 탐색)
	Component* findEnemy = ComponentSystem::GetInstance()->FindComponentInRange(map, this, 4, compareTypeList);
}