#pragma once
#include <Windows.h>
HINSTANCE;
class GameSystem
{
private:
	static GameSystem* _instance;
public:
	static GameSystem* GetInstance();
	
	bool InitSystem(HINSTANCE hInstance, int nCmdShow);
	int Update();
private:
	GameSystem();
public:
	~GameSystem();
};