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
public:
	void Init(std::wstring name);
	void DInit();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();
	Map* GetMap() { return _map; }
};