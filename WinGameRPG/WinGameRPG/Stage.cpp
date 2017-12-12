#include "Stage.h"
#include "ComponentSystem.h"
#include "Map.h"
#include "LifeNPC.h"
#include "StageLoader.h"
#include "DefaultStageLoader.h"
#include "LifeStageLoader.h"
#include "PathfinderStageLoader.h"
#include"TileCell.h"
#include"LifeNPC.h"
Stage::Stage()
{
	_stageLoader = NULL;
}

Stage::~Stage()
{
	if (NULL != _stageLoader)
	{
		delete _stageLoader;
	}
	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		(*it)->DInit();
	}
	ComponentSystem::GetInstance()->RemoveAllComponents();
}
void Stage::Init(std::wstring mapName)
{
	_componentList.clear();

	_stageLoaderMap[L"Default"] = new DefaultStageLoader(this);
	_stageLoaderMap[L"Map3"] = new LifeStageLoader(this);
	_stageLoaderMap[L"Map4"] = new PathfinderStageLoader(this);

	_stageLoader = GetUnit(mapName);
	_stageLoader->CreateComponents();
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
		
		LifeNPC* npc = (LifeNPC*)(_stageLoader->CreateLifeNPC(L"npc", L"npc"));
		//npc->Init();
		npc->InitTilePosition(component->GetTileX(), component->GetTileY());
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
void Stage::AddStageComponent(Component* component)
{
	_componentList.push_back(component);
	component->Init();
}
StageLoader* Stage::GetUnit(std::wstring mapName)
{
	_map = new Map(mapName.c_str());
	AddStageComponent(_map);
	map<wstring, StageLoader*>::iterator it = _stageLoaderMap.find(mapName);
	if (it != _stageLoaderMap.end())
	{
		return it->second;
	}
	return _stageLoaderMap[L"Default"];
}
void Stage::CreatePathfinderNPC(TileCell* tileCell)
{
	LifeNPC* npc = (LifeNPC*)(_stageLoader->CreateLifeNPC(L"npc", L"npc"));
	npc->InitTilePosition(tileCell->GetTileX(), tileCell->GetTileY());

	if (tileCell->GetTileX() < tileCell->GetPrevPathFindingCell()->GetTileX())
	{
		npc->SetDirection(eDirection::RIGHT);
	}
	else if (tileCell->GetTileX() > tileCell->GetPrevPathFindingCell()->GetTileX())
	{
		npc->SetDirection(eDirection::LEFT);
	}
	else if (tileCell->GetTileY() < tileCell->GetPrevPathFindingCell()->GetTileY())
	{
		npc->SetDirection(eDirection::UP);
	}
	else if (tileCell->GetTileY() > tileCell->GetPrevPathFindingCell()->GetTileY())
	{
		npc->SetDirection(eDirection::DOWN);
	}
}