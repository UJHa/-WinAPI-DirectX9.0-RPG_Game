#pragma once
#include<Windows.h>
#define MAP_WIDTH 100
#define MAP_HEIGHT 100
struct Sprite;
class Map
{
private:
	Sprite* _testTileMap[MAP_HEIGHT][MAP_WIDTH];

	float _startX;
	float _startY;
	float _deltaX;
	float _deltaY;
public:
	Map(LPCWSTR fileName);
	~Map();

	void Init();
	void DInit();
	void Update(int deltaTime);
	void render();
	void Release();
	void Reset();
	void Scroll(float moveX, float moveY);
};