#pragma once
#include<string>
#include "Component.h"
class Sprite;
class Effect : public Component
{
public:
	Effect();
	~Effect();

private:
	std::wstring _scriptName;
	std::wstring _textureFileName;
	Sprite* _sprite;
	float _posX;
	float _posY;
public:
	void Init();
	void DInit();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();

	void MoveDeltaPosition(float deltaX, float deltaY);
	void SetPosition(float posX, float posY);
	void InitTilePosition(int tileX, int tileY);
};