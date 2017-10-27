#pragma once
#include"Character.h"
class Player : public Character
{
private:

public:
	Player(LPCWSTR name);
	~Player();
	//AI
public:
	void UpdateAI();
};

