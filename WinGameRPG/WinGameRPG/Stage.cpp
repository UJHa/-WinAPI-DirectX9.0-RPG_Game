#include "Stage.h"
#include "ComponentSystem.h"
#include "Map.h"
#include "LifeNPC.h"
#include "Unit.h"
#include "DefaultUnit.h"
#include "LifeUnit.h"
#include "PathfinderStageLoader.h"
Stage::Stage()
{
	_unit = NULL;
}

Stage::~Stage()
{
	if (NULL != _unit)
	{
		delete _unit;
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

	_unitMap[L"Default"] = new DefaultUnit(this);
	_unitMap[L"Map3"] = new LifeUnit(this);
	_unitMap[L"Map4"] = new PathfinderStageLoader(this);

	_unit = GetUnit(mapName);
	_unit->CreateComponents();

	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		if (0 == (*it)->GetName().compare(L"player") )
		{
			_map->InitViewer(*it);
			break;
		}
	}
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
		
		LifeNPC* npc = (LifeNPC*)(_unit->CreateLifeNPC(L"npc", L"npc"));
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
Unit* Stage::GetUnit(std::wstring mapName)
{
	_map = new Map(mapName.c_str());
	AddStageComponent(_map);
	map<wstring, Unit*>::iterator it = _unitMap.find(mapName);
	if (it != _unitMap.end())
	{
		return it->second;
	}
	return _unitMap[L"Default"];
}