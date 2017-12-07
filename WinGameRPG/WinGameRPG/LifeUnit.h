#pragma once
#include "Unit.h"
class LifeUnit : public Unit
{
public:
	LifeUnit(Stage* stage);
	~LifeUnit();

	void CreateComponents();
	Component* CreateLifeNPC(wstring scriptName, wstring pngName);
};