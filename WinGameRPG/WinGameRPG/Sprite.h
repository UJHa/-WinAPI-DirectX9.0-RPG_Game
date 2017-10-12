#pragma once
#include<D3DX9.h>
#include<vector>
struct Frame;
class Sprite
{
//DirectX
private:
	LPDIRECT3DTEXTURE9 _texture;
	RECT _srcTextureRect;
	D3DCOLOR _textureColor;
	D3DXIMAGE_INFO _textureInfo;

	LPDIRECT3DDEVICE9 _device3d;
	LPD3DXSPRITE _sprite;
private:
	//Frame* _frame;
	std::vector<Frame*> _frameList;
	int _currentFrame;
public:
	Sprite();
	~Sprite();

	void Init(LPDIRECT3DDEVICE9 device3d, LPD3DXSPRITE sprite);
	void DInit();
	void Render();
	void Release();
	void Reset(LPDIRECT3DDEVICE9 device3d, LPD3DXSPRITE sprite);
};