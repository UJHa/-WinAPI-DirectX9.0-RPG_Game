#pragma once
#include<Windows.h>
#include<vector>
#include"Component.h"
struct Sprite;
class Map : public Component
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
	Map(LPCWSTR name);
	~Map();

	void Init();
	void DInit();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();
	void Scroll(float moveX, float moveY);
};