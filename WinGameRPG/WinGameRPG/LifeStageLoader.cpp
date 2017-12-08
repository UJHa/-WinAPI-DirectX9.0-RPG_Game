#include "LifeStageLoader.h"
#include "LifePlayer.h"
#include "Stage.h"
#include "Map.h"
#include "LifeNPC.h"
LifeStageLoader::LifeStageLoader(Stage* stage) : StageLoader(stage)
{
}

LifeStageLoader::~LifeStageLoader()
{
}
void LifeStageLoader::CreateComponents()
{
	for (int i = 0; i < 200; i++)
	{
		Component* component = CreateLifeNPC(L"npc", L"npc");
	}
	LifePlayer* player = new LifePlayer(L"player", L"player", L"player");
	_stage->AddStageComponent(player);
	_stage->GetMap()->InitViewer(player);
}
Component* LifeStageLoader::CreateLifeNPC(wstring scriptName, wstring pngName)
{
	SetName(L"lifeNpc_%d");
	_lifeNpcCount++;
	Component* component = new LifeNPC(_name, L"npc", L"npc");
	_stage->AddStageComponent(component);
	return component;
}