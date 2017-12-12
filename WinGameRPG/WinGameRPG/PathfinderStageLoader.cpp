#include "PathfinderStageLoader.h"
#include "Stage.h"
#include "Map.h"
#include<list>
#include "PathfinderPlayer.h"
#include "Monster.h"
#include "PathfinderMonster.h"
#include "LifeNPC.h"
PathfinderStageLoader::PathfinderStageLoader(Stage* stage) : StageLoader(stage)
{
}

PathfinderStageLoader::~PathfinderStageLoader()
{
}
void PathfinderStageLoader::CreateComponents()
{
	StageLoader::CreateComponents();
	Player* player = new PathfinderPlayer(L"player", L"player", L"player");
	_stage->AddStageComponent(player);
	Monster* monster = new PathfinderMonster(L"monster", L"monster", L"monster");
	_stage->AddStageComponent(monster);

	TileCell* targetCell = _stage->GetMap()->GetTileCell(monster->GetTileX(), monster->GetTileY());
	player->SetTargetTileCell(targetCell);
	
	int midTileX = _stage->GetMap()->GetWidth() / 2;
	int midTileY = _stage->GetMap()->GetHeight() / 2;
	std::list<Component*> comList = _stage->GetMap()->GetTileComponentList(midTileX, midTileY);
	_stage->GetMap()->InitViewer(comList.front());
}
Component* PathfinderStageLoader::CreateLifeNPC(wstring scriptName, wstring pngName)
{
	SetName(L"lifeNpc_%d");
	_lifeNpcCount++;
	Component* component = new LifeNPC(_name, L"npc", L"npc");
	_stage->AddStageComponent(component);
	return component;
}