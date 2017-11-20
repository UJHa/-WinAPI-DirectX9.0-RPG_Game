#pragma once
#include"Character.h"
class Player : public Character
{
private:
public:
	Player(LPCWSTR name, LPCWSTR scriptName, LPCWSTR pngName);
	~Player();
	//AI
public:
	void UpdateAI();
	Component* Collision(std::list<Component*>& collisionList);
};

