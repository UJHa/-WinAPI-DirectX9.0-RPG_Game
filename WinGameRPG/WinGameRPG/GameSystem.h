#pragma once
#include <Windows.h>
#include<D3DX11.h>
HINSTANCE;
class GameSystem
{
private:
	static GameSystem* _instance;
	GameSystem();
public:
	static GameSystem* GetInstance();
	
	bool InitSystem(HINSTANCE hInstance, int nCmdShow);
	int Update();
	bool InitDirect3D();
private:
	ID3D11Device* _d3dDevice;
	ID3D11DeviceContext* _d3dDeviceContext;
	UINT _4xMsaaQuality;
	bool _isEnable4xMsaa;
};