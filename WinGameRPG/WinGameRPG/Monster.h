#pragma once
#include<Windows.h>
#include"Character.h"
class Monster : public Character
{
private:
public:
	Monster(LPCWSTR name, LPCWSTR scriptName, LPCWSTR pngName);
	~Monster();
	void UpdateAI();
};