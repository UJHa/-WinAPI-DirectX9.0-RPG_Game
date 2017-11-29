#pragma once
#include "Character.h"
class LifeNPC : public Character
{
public:
	LifeNPC(wstring name, wstring scriptName, wstring pngName);
	~LifeNPC();
public:
	void UpdateAI();
	void UpdateText();
};