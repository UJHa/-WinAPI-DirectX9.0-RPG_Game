#pragma once
#include"Component.h"
class Sprite;
class TileObject : public Component
{
private:
	Sprite* _sprite;
	float _posX;
	float _posY;
public:
	TileObject(LPCWSTR name, Sprite* sprite);
	virtual ~TileObject();

	virtual void Init();
	virtual void DInit();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void Release();
	virtual void Reset();

	void MoveDeltaPosition(float deltaX, float deltaY);
	void SetPosition(float posX, float posY);
};