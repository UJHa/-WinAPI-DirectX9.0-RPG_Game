#pragma once
#include<Windows.h>
#include<list>
class Component;
class Map;
class Stage
{
public:
	Stage();
	~Stage();

private:
	std::list<Component*> _componentList;
	Map* _map;
	int _lifeNpcCount;
	std::list<Component*> _createBaseComponentList;
	std::list<Component*> _removeComponentList;
public:
	void Init(std::wstring name);
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
};