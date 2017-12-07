#pragma once
#include<Windows.h>
#include<list>
#include<map>
class Component;
class Map;
class Unit;
class Stage
{
public:
	Stage();
	~Stage();

private:
	std::list<Component*> _componentList;
	Map* _map;
	//int _lifeNpcCount;
	std::list<Component*> _createBaseComponentList;
	std::list<Component*> _removeComponentList;
	Unit* _bp;
	std::map<std::wstring, Unit*> _unitMap;
public:
	void Init(std::wstring mapName);
	void DInit();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();

	Map* GetMap() { return _map; }
	void CreateLifeNPC(Component* component);
	void DestroyLifeNPC(int tileX, int tileY, Component* component);
	void CheckDestroyLifeNPC(Component* component);
	void UpdateBaseComponentList();
	void UpdateRemoveComponentList();
	void AddStageComponent(Component* component);
private:
	Unit* _unit;
public:
	//Unit setting
	Unit* GetUnit(std::wstring mapName);
};