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
	TileObject(wstring name, Sprite* sprite, int tileX, int tileY);
	virtual ~TileObject();

	virtual void Init();
	virtual void DInit();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void Release();
	virtual void Reset();

	void MoveDeltaPosition(float deltaX, float deltaY);
	void SetPosition(float posX, float posY);

private:
	float _distanceWeight;
public:
	void SetDistanceWeight(float distanceWeight) { _distanceWeight = distanceWeight; }
	float GetDistanceWeight() { return _distanceWeight; }
};