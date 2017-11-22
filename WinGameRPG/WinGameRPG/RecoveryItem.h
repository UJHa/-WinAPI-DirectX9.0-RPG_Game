#pragma once
#include"Component.h"
#include<string>
class Sprite;
class RecoveryItem : public Component
{
public:
	RecoveryItem(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textureFileName);
	~RecoveryItem();

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
};