#pragma once
#include<string>
#include "Player.h"
using namespace std;
class LifePlayer : public Player
{
public:
	LifePlayer(wstring name, wstring scriptName, wstring pngName);
	~LifePlayer();
public:
	void InitState();
};