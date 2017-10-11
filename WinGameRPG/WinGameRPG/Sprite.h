#pragma once
#include<D3DX9.h>
class Sprite
{
private:
	LPDIRECT3DTEXTURE9 _texture;
	RECT _srcTextureRect;
	D3DCOLOR _textureColor;
	D3DXIMAGE_INFO _textureInfo;

	LPD3DXSPRITE _sprite;
public:
	Sprite();
	~Sprite();

	void Init(LPDIRECT3DDEVICE9 device3d, LPD3DXSPRITE sprite);
	void DInit();
	void Render();
	void Release();
	void Reset(LPDIRECT3DDEVICE9 device3d, LPD3DXSPRITE sprite);
};