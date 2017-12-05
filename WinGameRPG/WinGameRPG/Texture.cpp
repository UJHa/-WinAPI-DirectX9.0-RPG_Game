#include"Texture.h"
#include"GameSystem.h"
Texture::Texture()
{
	_texture = NULL;
}

Texture::~Texture()
{
}
void Texture::Init(const wchar_t* fileName)
{
	//Texture
	{
		//파일로 이미지 폭과 너비를 가져온다.
		HRESULT hr = D3DXGetImageInfoFromFile(fileName, &_textureInfo);
		if (FAILED(hr))
		{
			MessageBox(0, L"D3DXGetImageInfoFromFile 에러입니다.", L"ErrorMessage", 0);
			return;
		}
		//텍스쳐 생성
		hr = D3DXCreateTextureFromFileEx(
			GameSystem::GetInstance()->GetDevice3d(),
			fileName,
			_textureInfo.Width,
			_textureInfo.Height,
			0, 0,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_ARGB(255, 255, 255, 255),
			&_textureInfo,
			NULL,
			&_texture
		);
	}
}
void Texture::DInit()
{
	RELEASE_COM(_texture);
}
void Texture::Release()
{
	RELEASE_COM(_texture);
}
LPDIRECT3DTEXTURE9 Texture::GetTextureDX()
{
	return _texture;
}