#pragma once
#include <Windows.h>
//#include<D3DX11.h>
#include<D3DX9.h>
#include<D3D9.h>
#define RELEASE_COM(x) {if(x){x->Release();x=NULL;}}
#define SAVE_DELETE(x) {if(x){delete x;x=NULL;}}
struct GameTimer;
class GameSystem
{
private:
	static GameSystem* _instance;
	GameSystem();
public:
	~GameSystem();
	static GameSystem* GetInstance();
	
	bool InitSystem(HINSTANCE hInstance, int nCmdShow);
	int Update();
	bool InitDirect3D();
private:
	UINT _4xMsaaQuality;
	HWND _hMainWnd;
	//ID3D11Device* _d3dDevice;
	//ID3D11DeviceContext* _d3dDeviceContext;
	//bool _isEnable4xMsaa;
	//IDXGISwapChain* _swapChain;
	//ID3D11RenderTargetView* _renderTargetView;
	//ID3D11Texture2D* _depthStencilBuffer;
	//ID3D11DepthStencilView* _depthStencilView;

	//D3D11_VIEWPORT _screenViewport;
	LPDIRECT3DDEVICE9 _device3d;
	LPD3DXSPRITE _sprite;
	bool _isFullScreen;
private:
	GameTimer* _gameTimer;
};