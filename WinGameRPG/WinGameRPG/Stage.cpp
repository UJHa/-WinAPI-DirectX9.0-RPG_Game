#include "ComponentSystem.h"
#include "Stage.h"
#include "Map.h"
#include "NPC.h"
#include "Player.h"
#include "Monster.h"
#include "RecoveryItem.h"
Stage::Stage()
{
}

Stage::~Stage()
{
	ComponentSystem::GetInstance()->RemoveAllComponents();
}
void Stage::Init(std::wstring name)
{
	_componentList.clear();
	_map = new Map(name.c_str());
	_componentList.push_back(_map);

	for (int i = 0; i < 0; i++)
	{
		WCHAR name[256];
		wsprintf(name, L"recovery_item_%d", i);
		RecoveryItem* recoveryItem = new RecoveryItem(name, L"recovery_item", L"item_sprites");
		_componentList.push_back(recoveryItem);
	}
	WCHAR playerName[256];
	wsprintf(playerName, L"player");
	Player* player = new Player(playerName, L"player", L"player");
	_componentList.push_back(player);

	for (int i = 0; i < 0; i++)
	{
		WCHAR name[256];
		wsprintf(name, L"npc_%d", i);
		NPC* npc = new NPC(name, L"npc", L"npc");
		_componentList.push_back(npc);
	}
	for (int i = 0; i < 0; i++)
	{
		WCHAR name[256];
		wsprintf(name, L"monster_%d", i);
		Monster* monster = new Monster(name, L"monster", L"monster");
		_componentList.push_back(monster);
	}

	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		(*it)->Init();
	}

	_map->InitViewer(player);
}
void Stage::DInit()
{
	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		(*it)->DInit();
	}
}
void Stage::Update(float deltaTime)
{
	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		(*it)->Update(deltaTime);
	}
}
void Stage::Render()
{
	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		(*it)->Render();
	}
}
void Stage::Release()
{
	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		(*it)->Release();
	}
}
void Stage::Reset()
{
	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		(*it)->Reset();
	}
}