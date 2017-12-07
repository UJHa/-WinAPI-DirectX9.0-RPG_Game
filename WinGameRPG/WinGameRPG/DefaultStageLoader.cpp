#include "DefaultStageLoader.h"
#include "Player.h"
#include "Stage.h"
#include "NPC.h"
#include "Monster.h"
DefaultStageLoader::DefaultStageLoader(Stage* stage) : StageLoader(stage)
{
}

DefaultStageLoader::~DefaultStageLoader()
{
}
void DefaultStageLoader::CreateComponents()
{
	for (int i = 0; i < 2; i++)
	{
		Component* component = CreateNPC(L"npc", L"npc");
	}
	for (int i = 0; i < 1; i++)
	{
		Component* component = CreateMonster(L"monster", L"monster");
	}

	Player* player = new Player(L"player", L"player", L"player");
	_stage->AddStageComponent(player);
}
Component* DefaultStageLoader::CreateNPC(wstring scriptName, wstring pngName)
{
	SetName(L"npc_%d");
	_lifeNpcCount++;
	Component* component = new NPC(_name, scriptName, pngName);
	_stage->AddStageComponent(component);
	return component;
}
Component* DefaultStageLoader::CreateMonster(wstring scriptName, wstring pngName)
{
	SetName(L"monster_%d");
	_lifeNpcCount++;
	Component* component = new Monster(_name, scriptName, pngName);
	_stage->AddStageComponent(component);
	return component;
}