#pragma once
#include<Windows.h>
#include<vector>
#include<list>
#include"Component.h"
class Sprite;
class TileCell;
using namespace std;
class Map : public Component
{
private:
	vector<vector<TileCell*>> _tileMap;
	int _width;
	int _height;

	float _startX;
	float _startY;
	float _deltaX;
	float _deltaY;

	int _tileSize;

	vector<Sprite*> _spriteList;
public:
	Map(LPCWSTR name);
	~Map();

	void Init();
	void DInit();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();
	void Scroll(float moveX, float moveY);

	int GetPositionX(int tileX, int tileY);
	int GetPositionY(int tileX, int tileY);
	bool GetTileCollisionList(int tileX, int tileY, std::list<Component*>& collisionList);
	std::list<Component*> GetTileComponentList(int tileX, int tileY);
	void setTileComponent(int tileX, int tileY, Component* component, bool isRender);
	void ResetTileComponent(int tileX, int tileY, Component* component);
	bool CanMoveTileMap(int tileX, int tileY);
	int GetWidth();
	int GetHeight();
	//Viewer
private:
	Component* _viewer;
public:
	void InitViewer(Component* viewer);
};