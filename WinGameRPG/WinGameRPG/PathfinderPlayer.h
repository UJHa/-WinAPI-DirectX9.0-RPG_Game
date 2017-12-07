#pragma once
#include "Player.h"
class PathfinderPlayer : public Player
{
public:
	PathfinderPlayer(wstring name, wstring scriptName, wstring pngName);
	~PathfinderPlayer();
public:
	void UpdateAI();
	//AI
public:
	void InitState();
};