#pragma once
#include "Monster.h"
class PathfinderMonster : public Monster
{
public:
	PathfinderMonster(wstring name, wstring scriptName, wstring pngName);
	~PathfinderMonster();

public:
	void UpdateAI();

};