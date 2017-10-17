#include "GameSystem.h"
#include <Windows.h>
#include "GameTimer.h"
#include "Sprite.h"
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lparam) {
	switch (msg)
	{
	case WM_KEYDOWN:
		if (VK_ESCAPE == wParam)
			DestroyWindow(hWnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		MessageBox(0, L"Hello World", L"Hello", MB_OK);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lparam);
}
GameSystem* GameSystem::_instance = NULL;
GameSystem::GameSystem()
{
	_isFullScreen = false;
	if (_isFullScreen)
	{
		_WindowWidth = 1920;
		_WindowHeight = 1080;
	}
	else
	{
		_WindowWidth = 1280;
		_WindowHeight = 800;
	}
	//_testSprite = NULL;
	//_testSpriteList.clear();
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			_testTileMap[x][y] = NULL;
		}
	}
}
GameSystem::~GameSystem()
{
	/*if (NULL != _testSprite)
	{
		_testSprite->DInit();
		delete _testSprite;
		_testSprite = NULL;
	}*/
	/*for (int i = 0; i < _testSpriteList.size(); i++)
	{
		_testSpriteList[i]->DInit();
		delete _testSpriteList[i];
	}
	_testSpriteList.clear();*/
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			_testTileMap[x][y]->DInit();
			delete _testTileMap[x][y];
		}
	}
	RELEASE_COM(_sprite);
	RELEASE_COM(_device3d);
}
GameSystem* GameSystem::GetInstance()
{
	if (NULL == _instance)
		_instance = new GameSystem();
	return _instance;
}
bool GameSystem::InitSystem(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"Base";
	//윈도우 등록
	if (!RegisterClass(&wc))
	{
		return false;
	}
	//윈도우 생성
	DWORD style;
	if (_isFullScreen)
	{
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	}
	else
	{
		style = WS_OVERLAPPEDWINDOW;
	}
	_hMainWnd = CreateWindow(
		L"Base",
		L"2D_RPG_TileMap",
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,
		0,
		hInstance,
		0);

	if (false == _isFullScreen)
	{
		RECT clientRect;
		GetClientRect(_hMainWnd, &clientRect);

		int addWidth = _WindowWidth - clientRect.right;
		int addHeight = _WindowHeight - clientRect.bottom;
		int finalWidth = _WindowWidth + addWidth;
		int finalHeight = _WindowHeight + addHeight;
		MoveWindow(_hMainWnd, 0, 0, finalWidth, finalHeight, TRUE);
	}
	//윈도우 출력
	ShowWindow(_hMainWnd, nCmdShow);
	//윈도우 업데이트
	UpdateWindow(_hMainWnd);
	if (false == InitDirect3D())
	{
		return false;
	}

	{
		/*Sprite* sprite1 = new Sprite(L"character_sprite.png", L"char_sprite_01.json");
		sprite1->Init();
		_testSpriteList.push_back(sprite1);
		Sprite* sprite2 = new Sprite(L"character_sprite.png", L"char_sprite_02.json");
		sprite2->Init();
		_testSpriteList.push_back(sprite2);
		Sprite* sprite3 = new Sprite(L"character_sprite.png", L"char_sprite_03.json");
		sprite3->Init();
		_testSpriteList.push_back(sprite3);
		Sprite* sprite4 = new Sprite(L"character_sprite.png", L"char_sprite_04.json");
		sprite4->Init();
		_testSpriteList.push_back(sprite4);*/
		for (int y = 0; y < 16; y++)
		{
			for (int x = 0; x < 16; x++)
			{
				Sprite* sprite;
				int randValue = rand() % 4;
				switch (randValue)
				{
				case 0:
					sprite = new Sprite(L"character_sprite.png", L"char_sprite_01.json");
					break;
				case 1:
					sprite = new Sprite(L"character_sprite.png", L"char_sprite_02.json");
					break;
				case 2:
					sprite = new Sprite(L"character_sprite.png", L"char_sprite_03.json");
					break;
				case 3:
					sprite = new Sprite(L"character_sprite.png", L"char_sprite_04.json");
					break;
				default:
					break;
				}
				sprite->Init();
				_testTileMap[x][y] = sprite;
			}
		}
	}
	//_testSprite = new Sprite(L"character_sprite.png",L"jsonText.json");
	//_testSprite->Init();
	return true;
}
int GameSystem::Update()
{
	MSG msg = { 0 };
	int ref = 1;
	GameTimer* _gameTimer = new GameTimer();
	_gameTimer->Reset();
	float frameTime = 1.0f / 60.f;	//60프레임
	float frameDuration = 0;
	float colorRed = 0.0f;
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//게임업데이트
			_gameTimer->Update();
			float deltaTime = _gameTimer->GetDeltaTime();
			frameDuration += deltaTime;

			//_testSpriteList[3]->Update(deltaTime);
			/*for (int i = 0; i < _testSpriteList.size(); i++)
			{
				_testSpriteList[i]->Update(deltaTime);
			}*/
			//_testSprite->Update(deltaTime);
			for (int y = 0; y < 16; y++)
			{
				for (int x = 0; x < 16; x++)
				{
					_testTileMap[x][y]->Update(deltaTime);
				}
			}
			if (frameTime <= frameDuration)
			{
				wchar_t timeCheck[256];
				swprintf(timeCheck, L"frameDuration %f\n", frameDuration);
				OutputDebugString(timeCheck);

				frameDuration = 0.0f;

				_device3d->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 100, 0), 0.0f, 0);

				_device3d->BeginScene();

				_sprite->Begin(D3DXSPRITE_ALPHABLEND);

				//_testSpriteList[3]->Render();
				/*for (int i = 0; i < _testSpriteList.size(); i++)
				{
					_testSpriteList[3]->Render();
				}*/
				//_testSprite->Render();
				int tileSize = 32;
				float startX = 0.0f + tileSize / 2;
				float startY = 0.0f + tileSize / 2;
				float posX = startX;
				float posY = startY;
				for (int y = 0; y < 16; y++)
				{
					for (int x = 0; x < 16; x++)
					{
						_testTileMap[x][y]->SetPosition(posX, posY);
						_testTileMap[x][y]->Render();
						posX += tileSize;
					}
					posX = startX;
					posY += tileSize;

				}
				
				_sprite->End();

				_device3d->EndScene();

				CheckDeviceLost();

				_device3d->Present(NULL, NULL, NULL, NULL);
			}

			/*wchar_t timeCheck[256];
			swprintf(timeCheck,L"deltaTime %f\n",deltaTime);
			OutputDebugString(timeCheck);*/
		}
	}
	return (int)msg.wParam;
}
bool GameSystem::InitDirect3D()
{
	LPDIRECT3D9 direct3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (NULL == direct3d)
	{
		MessageBox(0, L"false", L"create Filed", MB_OK);
		return false;
	}

	ZeroMemory(&_d3dpp, sizeof(_d3dpp));
	_d3dpp.BackBufferWidth = _WindowWidth;
	_d3dpp.BackBufferHeight = _WindowHeight;

	if (_isFullScreen)
	{
		_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	}

	_d3dpp.BackBufferCount = 1;
	_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	_d3dpp.hDeviceWindow = _hMainWnd;
	_d3dpp.Windowed = (!_isFullScreen);
	_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	D3DCAPS9 caps;
	HRESULT hr = direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	if (FAILED(hr))
	{
		MessageBox(0, L"GetDeviceCaps 에러입니다.", L"ErrorMessage", 0);
		return false;
	}

	DWORD behavior;
	if ((caps.DeviceType & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 || (caps.VertexShaderVersion < D3DVS_VERSION(1, 1)))
	{
		behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
	else
	{
		behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}

	hr = direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hMainWnd, behavior, &_d3dpp, &_device3d);
	if (FAILED(hr))
	{
		MessageBox(0, L"CreateDevice 에러입니다.", L"ErrorMessage", 0);
		return false;
	}

	hr = D3DXCreateSprite(_device3d, &_sprite);
	if (FAILED(hr))
	{
		MessageBox(0, L"D3DXCreateSprite 에러입니다.", L"ErrorMessage", 0);
		return false;
	}
	return true;
}
void GameSystem::CheckDeviceLost()
{
	HRESULT hr = _device3d->TestCooperativeLevel();
	if (FAILED(hr))
	{
		if (D3DERR_DEVICELOST == hr)
		{
			Sleep(100);
			return;
		}
		else if (D3DERR_DEVICENOTRESET == hr)
		{
			/*for (int i = 0; i < _testSpriteList.size(); i++)
			{
				_testSpriteList[i]->Release();
			}*/
			//_testSprite->Release();
			for (int y = 0; y < 16; y++)
			{
				for (int x = 0; x < 16; x++)
				{
					_testTileMap[x][y]->Release();
				}
			}
			hr = _device3d->Reset(&_d3dpp);
			InitDirect3D();
			/*for (int i = 0; i < _testSpriteList.size(); i++)
			{
				_testSpriteList[i]->Reset();
			}*/
			//_testSprite->Reset();
			for (int y = 0; y < 16; y++)
			{
				for (int x = 0; x < 16; x++)
				{
					_testTileMap[x][y]->Reset();
				}
			}
		}
	}
}
int GameSystem::GetWindowWidth()
{
	return _WindowWidth;
}
int GameSystem::GetWindowHeight()
{
	return _WindowHeight;
}
LPD3DXSPRITE GameSystem::GetSprite()
{
	return _sprite;
}
LPDIRECT3DDEVICE9 GameSystem::GetDevice3d()
{
	return _device3d;
}