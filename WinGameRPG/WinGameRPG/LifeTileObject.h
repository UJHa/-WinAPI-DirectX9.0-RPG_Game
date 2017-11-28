#pragma once
#include "TileObject.h"
class LifeTileObject : public TileObject
{
public:
	LifeTileObject(int tileX, int tileY, LPCWSTR name, Sprite* sprite);
	~LifeTileObject();
public:
	void Update(float deltaTime);
};