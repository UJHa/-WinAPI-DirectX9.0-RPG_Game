#include "LifeUnit.h"
#include "LifePlayer.h"
#include "Stage.h"
#include "LifeNPC.h"
LifeUnit::LifeUnit(Stage* stage) : Unit(stage)
{
}

LifeUnit::~LifeUnit()
{
}
void LifeUnit::CreateComponents()
{
	for (int i = 0; i < 200; i++)
	{
		Component* component = CreateLifeNPC(L"npc", L"npc");
	}
	LifePlayer* player = new LifePlayer(L"player", L"player", L"player");
	_stage->AddStageComponent(player);
}
Component* LifeUnit::CreateLifeNPC(wstring scriptName, wstring pngName)
{
	SetName(L"lifeNpc_%d");
	_lifeNpcCount++;
	Component* component = new LifeNPC(_name, L"npc", L"npc");
	_stage->AddStageComponent(component);
	return component;
}