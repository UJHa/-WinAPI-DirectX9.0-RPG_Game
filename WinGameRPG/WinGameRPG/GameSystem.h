#pragma once
#include <Windows.h>
//#include<D3DX11.h>
#include<D3DX9.h>
#include<D3D9.h>

#define RELEASE_COM(x) {if(x){x->Release();x=NULL;}}
#define SAVE_DELETE(x) {if(x){delete x;x=NULL;}}
struct GameTimer;
struct Sprite;
class GameSystem
{
private:
	static GameSystem* _instance;
	GameSystem();
public:
	~GameSystem();
	static GameSystem* GetInstance();
private:
	D3DPRESENT_PARAMETERS _d3dpp;
	UINT _4xMsaaQuality;
	HWND _hMainWnd;
	LPDIRECT3DDEVICE9 _device3d;
	LPD3DXSPRITE _sprite;

	bool _isFullScreen;
private:
	int _WindowWidth;
	int _WindowHeight;
	GameTimer* _gameTimer;
	Sprite* _testSprite;
	/*LPDIRECT3DTEXTURE9 _texture;
	RECT _srcTextureRect;
	D3DCOLOR _textureColor;
	D3DXIMAGE_INFO _textureInfo;*/
public:
	bool InitSystem(HINSTANCE hInstance, int nCmdShow);
	int Update();
	bool InitDirect3D();
	void CheckDeviceLost();
};