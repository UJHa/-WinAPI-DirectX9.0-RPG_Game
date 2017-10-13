#pragma once
#include<D3dx9.h>
class Texture
{
private:
	LPDIRECT3DTEXTURE9 _texture;
	D3DXIMAGE_INFO _textureInfo;
public:
	Texture();
	~Texture();
	void Init(const wchar_t* fileName);
	void DInit();
	void Release();
	LPDIRECT3DTEXTURE9 GetTextureDX();
};