#include "ComponentSystem.h"
#include "Stage.h"
#include "Map.h"
#include "NPC.h"
#include "Player.h"
#include "Monster.h"
#include "RecoveryItem.h"
#include "LifeNPC.h"
#include "LifePlayer.h"
Stage::Stage()
{
}

Stage::~Stage()
{
	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		(*it)->DInit();
	}
	ComponentSystem::GetInstance()->RemoveAllComponents();
}
void Stage::Init(std::wstring name)
{
	_componentList.clear();
	_map = new Map(name.c_str());
	_componentList.push_back(_map);
	Player* player = NULL;

	if (L"Map3" == name)
	{
		_lifeNpcCount = 0;
		for (int i = 0; i < 300; i++)
		{
			//CreateLifeNPC();
			WCHAR name[256];
			wsprintf(name, L"lifeNpc_%d", _lifeNpcCount);
			_lifeNpcCount++;
			LifeNPC* npc = new LifeNPC(name, L"npc", L"npc");
			_componentList.push_back(npc);
		}
		player = new LifePlayer(L"player", L"player", L"player");
	}
	else
	{
		for (int i = 0; i < 0; i++)
		{
			WCHAR name[256];
			wsprintf(name, L"recovery_item_%d", i);
			RecoveryItem* recoveryItem = new RecoveryItem(name, L"recovery_item", L"item_sprites");
			_componentList.push_back(recoveryItem);
		}
		for (int i = 0; i < 2; i++)
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
		player = new Player(L"player", L"player", L"player");
	}
	_componentList.push_back(player);
	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		(*it)->Init();
	}

	_map->InitViewer(player);
}
void Stage::DInit()
{
}
void Stage::Update(float deltaTime)
{
	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		(*it)->Update(deltaTime);
	}
	UpdateBaseComponentList();
	UpdateRemoveComponentList();
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
void Stage::CreateLifeNPC(Component* component)
{
	//component->
	_createBaseComponentList.push_back(component);
}
void Stage::DestroyLifeNPC(int tileX, int tileY, Component* component)
{
	_map->ResetTileComponent(tileX, tileY, component);
	component->SetCanMove(true);
	component->SetLive(false);

	_componentList.remove(component);
	ComponentSystem::GetInstance()->RemoveComponent(component);
}
void Stage::CheckDestroyLifeNPC(Component* component)
{
	_removeComponentList.push_back(component);
}
void Stage::UpdateBaseComponentList()
{
	for (std::list<Component*>::iterator it = _createBaseComponentList.begin(); it != _createBaseComponentList.end(); it++)
	{
		Component* component = (*it);
		WCHAR name[256];
		wsprintf(name, L"lifeNpc_%d", _lifeNpcCount);
		_lifeNpcCount++;
		LifeNPC* npc = new LifeNPC(name, L"npc", L"npc");
		npc->Init(component->GetTileX(), component->GetTileY());
		_componentList.push_back(npc);
	}
	_createBaseComponentList.clear();
}
void Stage::UpdateRemoveComponentList()
{
	for (std::list<Component*>::iterator it = _removeComponentList.begin(); it != _removeComponentList.end(); it++)
	{
		Component* component = (*it);
		DestroyLifeNPC(component->GetTileX(), component->GetTileY(), component);
	}
	_removeComponentList.clear();
}