#pragma once
#include<Windows.h>
#include<list>
#include"Character.h"
class Monster : public Character
{
private:
public:
	Monster(wstring name, wstring scriptName, wstring pngName);
	~Monster();
	void UpdateAI();
	Component* Collision(std::list<Component*>& collisionList);
};