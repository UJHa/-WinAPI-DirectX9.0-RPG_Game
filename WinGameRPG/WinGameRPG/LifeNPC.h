#pragma once
#include "Character.h"
class LifeNPC : public Character
{
public:
	LifeNPC(LPCWSTR name, LPCWSTR scriptName, LPCWSTR pngName);
	~LifeNPC();
public:
	void UpdateAI();
	void UpdateText();
};