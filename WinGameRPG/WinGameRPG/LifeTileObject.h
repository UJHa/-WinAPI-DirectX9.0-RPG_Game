#pragma once
#include "TileObject.h"
class LifeTileObject : public TileObject
{
public:
	LifeTileObject(LPCWSTR name, Sprite* sprite);
	~LifeTileObject();
public:
	void Update(float deltaTime);
};