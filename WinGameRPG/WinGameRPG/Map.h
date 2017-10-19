#pragma once
#include<Windows.h>
#include<vector>
//#define MAP_WIDTH 16
//#define MAP_HEIGHT 16
struct Sprite;
class Map
{
private:
	//Sprite* _tileMap[MAP_HEIGHT][MAP_WIDTH];
	std::vector<std::vector<Sprite*>> _tileMap;
	int _width;
	int _height;

	float _startX;
	float _startY;
	float _deltaX;
	float _deltaY;

	std::vector<Sprite*> _spriteList;
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