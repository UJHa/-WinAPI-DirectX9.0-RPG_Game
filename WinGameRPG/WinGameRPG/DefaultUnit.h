#pragma once
#include "Unit.h"
class DefaultUnit : public Unit
{
public:
	DefaultUnit(Stage* stage);
	~DefaultUnit();

	void CreateComponents();
	Component* CreateNPC(wstring scriptName, wstring pngName);
	Component* CreateMonster(wstring scriptName, wstring pngName);
};