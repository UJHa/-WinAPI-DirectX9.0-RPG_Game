#include "ComponentSystem.h"
#include "Stage.h"
#include "Map.h"
#include "NPC.h"
#include "Player.h"
#include "Monster.h"
#include "RecoveryItem.h"
#include "LifeNPC.h"
using namespace std;
Stage::Stage()
{
}

Stage::~Stage()
{
	/*for (list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		(*it)->DInit();
	}*/
	ComponentSystem::GetInstance()->RemoveAllComponents();
}
void Stage::Init(wstring name)
{
	_componentList.clear();
	_map = new Map(name);
	_componentList.push_back(_map);

	if (L"Map3" == name)
	{
		_lifeNpcCount = 0;
		for (int i = 0; i < 30; i++)
		{
			//CreateLifeNPC();
			WCHAR name[256];
			wsprintf(name, L"lifeNpc_%d", _lifeNpcCount);
			_lifeNpcCount++;
			LifeNPC* npc = new LifeNPC(name, L"npc", L"npc");
			_componentList.push_back(npc);
		}
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
	}
	Player* player = new Player(L"player", L"player", L"player");
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
void Stage::CreateLifeNPC(int tileX, int tileY)
{
	WCHAR name[256];
	wsprintf(name, L"lifeNpc_%d", _lifeNpcCount);
	_lifeNpcCount++;
	LifeNPC* npc = new LifeNPC(name, L"npc", L"npc");
	npc->Init(tileX, tileY);
	_componentList.push_back(npc);
}
void Stage::DestroyLifeNPC(int tileX, int tileY, Component* tileCharacter)
{
	_map->ResetTileComponent(tileX, tileY, tileCharacter);
	tileCharacter->SetCanMove(true);
	tileCharacter->SetLive(false);
}
