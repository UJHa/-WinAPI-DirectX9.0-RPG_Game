#pragma once
#include<Windows.h>
#include<vector>
struct Sprite;
class Map
{
private:
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
	void Update(float deltaTime);
	void render();
	void Release();
	void Reset();
	void Scroll(float moveX, float moveY);
};