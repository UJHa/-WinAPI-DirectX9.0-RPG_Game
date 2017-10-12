#pragma once
#include<D3DX9.h>
class Frame
{
private:
	LPD3DXSPRITE _sprite;
	LPDIRECT3DTEXTURE9 _texture;

	RECT _srcTextureRect;
	D3DCOLOR _textureColor;

private:
	int _width;
	int _height;
public:
	Frame();
	~Frame();
	void Init(LPDIRECT3DDEVICE9 device3d, LPD3DXSPRITE sprite, LPDIRECT3DTEXTURE9 texture, int left, int top, int width, int height);
	void DInit();
	void Render();
	void Release();
	void Reset(LPDIRECT3DDEVICE9 device3d, LPD3DXSPRITE sprite);
};