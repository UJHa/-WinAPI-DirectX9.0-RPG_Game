#pragma once
#include<Windows.h>
#include<list>
#include<map>
class Component;
class Map;
class StageLoader;
class TileCell;
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
	std::map<std::wstring, StageLoader*> _stageLoaderMap;
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
	StageLoader* _stageLoader;
public:
	//Unit setting
	StageLoader* GetUnit(std::wstring mapName);
public:
	void CreatePathfinderNPC(TileCell* tileCell);
	void CreatePathfindingMark(TileCell* tileCell);
public:
	void CreateEffect(TileCell* tileCell);
	void RemoveEffect(TileCell* tileCell);
};