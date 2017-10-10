#include "GameSystem.h"
#include <Windows.h>
#include "GameTimer.h"
#include<string>
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
	//_isEnable4xMsaa = false;
	_isFullScreen = false;
}
GameSystem::~GameSystem()
{
	RELEASE_COM(_sprite);
	RELEASE_COM(_device3d);
	/*_swapChain->Release();
	_swapChain = 0;

	_d3dDevice->Release();
	_d3dDevice = 0;

	_d3dDeviceContext->Release();
	_d3dDeviceContext = 0;

	_renderTargetView->Release();
	_renderTargetView = 0;

	_depthStencilBuffer->Release();
	_depthStencilBuffer = 0;

	_depthStencilView->Release();
	_depthStencilView = 0;*/
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

		int addWidth = 1280 - clientRect.right;
		int addHeight = 800 - clientRect.bottom;
		int finalWidth = 1280 + addWidth;
		int finalHeight = 800 + addHeight;
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
			if (frameTime <= frameDuration)
			{
				wchar_t timeCheck[256];
				swprintf(timeCheck, L"frameDuration %f\n", frameDuration);
				OutputDebugString(timeCheck);

				frameDuration = 0.0f;

				//colorRed += 0.1f;
				//if(colorRed>1.0f)
				//	colorRed -= 1.0f;
				//float color[4];
				//color[0] = colorRed;	//R
				//color[1] = 0.2f;	//G
				//color[2] = 0.3f;	//B
				//color[3] = 1.0f;	//Alpha

				//_d3dDeviceContext->ClearRenderTargetView(_renderTargetView, color);
				//_d3dDeviceContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

				//_swapChain->Present(0, 0);
				_device3d->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 100, 0), 0.0f, 0);
				_device3d->BeginScene();

				_sprite->Begin(D3DXSPRITE_ALPHABLEND);

				//스프라이트 출력 전 모양 조정(위치,크기,회전)
				D3DXVECTOR2 spriteCenter = D3DXVECTOR2((float)_textureInfo.Width / 2.0f, (float)_textureInfo.Height / 2.0f);
				D3DXVECTOR2 translate = D3DXVECTOR2(1280.0f / 2.0f - (float)_textureInfo.Width / 2.0f, 800.0f / 2.0f - (float)_textureInfo.Height / 2.0f);
				D3DXVECTOR2 scaling = D3DXVECTOR2(1.0f, 1.0f);
				D3DXMATRIX matrix;
				D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, &scaling, &spriteCenter, 0.0f, &translate);
				_sprite->SetTransform(&matrix);

				_sprite->Draw(_texture, &_srcTextureRect, NULL, NULL, _textureColor);

				_sprite->End();

				_device3d->EndScene();
				_device3d->Present(NULL, NULL, NULL, NULL);
			}

			/*wchar_t timeCheck[256];
			swprintf(timeCheck,L"deltaTime %f\n",deltaTime);
			OutputDebugString(timeCheck);*/

			//게임 관련 드로우
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

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = 1280;
	d3dpp.BackBufferHeight = 800;

	if (_isFullScreen)
	{
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	}

	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = _hMainWnd;
	d3dpp.Windowed = (!_isFullScreen);
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

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

	hr = direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hMainWnd, behavior, &d3dpp, &_device3d);
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
	//Texture
	{
		//파일로 이미지 폭과 너비를 가져온다.
		hr = D3DXGetImageInfoFromFile(L"character_sprite.png",&_textureInfo);
		if (FAILED(hr))
		{
			MessageBox(0, L"D3DXGetImageInfoFromFile 에러입니다.", L"ErrorMessage", 0);
			return false;
		}
		//텍스쳐 생성
		hr = D3DXCreateTextureFromFileEx(
			_device3d, 
			L"character_sprite.png", 
			_textureInfo.Width, 
			_textureInfo.Height,
			1,0,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT, 
			D3DX_DEFAULT,
			D3DCOLOR_ARGB(255,255,255,255),
			&_textureInfo,
			NULL,
			&_texture
		);
		/*for (int i = 0; i < 3; i++)
		{
			_srcTextureRect.left = textureInfo.Width / 3 * i;
			_srcTextureRect.top = 0;
			_srcTextureRect.right = textureInfo.Width / 3 * (i + 1);
			_srcTextureRect.bottom = textureInfo.Height / 4;
		}*/
		_srcTextureRect.left = 0;
		_srcTextureRect.top = 0;
		_srcTextureRect.right = _textureInfo.Width;
		_srcTextureRect.bottom = _textureInfo.Height;

		_textureColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	}


	return true;
}