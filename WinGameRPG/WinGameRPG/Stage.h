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
public:
	void Init(std::wstring name);
	void DInit();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();
	Map* GetMap() { return _map; }
	void CreateLifeNPC(int tileX, int tileY);
	void DestroyLifeNPC(int tileX, int tileY, Component* tileCharacter);

};