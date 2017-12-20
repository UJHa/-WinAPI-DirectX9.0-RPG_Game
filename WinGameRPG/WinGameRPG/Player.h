#pragma once
#include"Character.h"
class Player : public Character
{
private:
public:
	Player(wstring name, wstring scriptName, wstring pngName);
	~Player();
	//AI
public:
	void UpdateAI();
	Component* Collision(std::list<Component*>& collisionList);
public:
	void InitState();
};

