#include "GameSystem.h"
#include <Windows.h>
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
	_isEnable4xMsaa = false;
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
	HWND hWnd = CreateWindow(L"Base", L"2D_RPG_TileMap", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, 0);
	//윈도우 출력
	ShowWindow(hWnd, nCmdShow);

	UpdateWindow(hWnd);
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
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//게임처리
		}
	}
	return (int)msg.wParam;
}
bool GameSystem::InitDirect3D()
{
	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr = D3D11CreateDevice(0,D3D_DRIVER_TYPE_HARDWARE,0,D3D10_CREATE_DEVICE_DEBUG,0,0,D3D11_SDK_VERSION,&_d3dDevice,&featureLevel,&_d3dDeviceContext);
	hr = _d3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &_4xMsaaQuality);	//4xMSAA 지원여부 확인
	DXGI_SWAP_CHAIN_DESC swapChain;
	swapChain.BufferDesc.Width = 1280;
	swapChain.BufferDesc.Height = 800;
	swapChain.BufferDesc.RefreshRate.Numerator = 60;
	swapChain.BufferDesc.RefreshRate.Denominator = 1;
	swapChain.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChain.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChain.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	if (_isEnable4xMsaa)
	{
		swapChain.SampleDesc.Count = 4;
		swapChain.SampleDesc.Quality = _4xMsaaQuality-1;
	}
	else
	{
		swapChain.SampleDesc.Count = 1;
		swapChain.SampleDesc.Quality = 0;
	}
	if (FAILED(hr))
	{
		MessageBox(0, L"??? 에러입니다.", L"ErrorMessage", MB_OK);
		return false;
	}

	return true;
}