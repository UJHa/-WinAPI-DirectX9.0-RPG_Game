#pragma once
#include<Windows.h>
#include"Component.h"
struct Sprite;
class Character : public Component
{
private:
	Sprite* _sprite;

	float _x;
	float _y;

	float _deltaX;
	float _deltaY;
public:
	Character(LPCWSTR name);
	~Character();

	void Init();
	void DInit();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();
};