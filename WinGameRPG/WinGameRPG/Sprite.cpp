#include"Sprite.h"
Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}
void Sprite::Init(LPDIRECT3DDEVICE9 device3d, LPD3DXSPRITE sprite)
{
	_sprite = sprite;
	//Texture
	{
		//파일로 이미지 폭과 너비를 가져온다.
		HRESULT hr = D3DXGetImageInfoFromFile(L"character_sprite.png", &_textureInfo);
		if (FAILED(hr))
		{
			MessageBox(0, L"D3DXGetImageInfoFromFile 에러입니다.", L"ErrorMessage", 0);
			return;
		}
		//텍스쳐 생성
		hr = D3DXCreateTextureFromFileEx(
			device3d,
			L"character_sprite.png",
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
}
void Sprite::DInit()
{
	RELEASE_COM(_texture);
}
void Sprite::Render()
{
	//스프라이트 출력 전 모양 조정(위치,크기,회전)
	D3DXVECTOR2 spriteCenter = D3DXVECTOR2((float)_textureInfo.Width / 2.0f, (float)_textureInfo.Height / 2.0f);
	D3DXVECTOR2 translate = D3DXVECTOR2((float)_WindowWidth / 2.0f - (float)_textureInfo.Width / 2.0f, (float)_WindowHeight / 2.0f - (float)_textureInfo.Height / 2.0f);
	D3DXVECTOR2 scaling = D3DXVECTOR2(1.0f, 1.0f);
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, &scaling, &spriteCenter, 0.0f, &translate);
	_sprite->SetTransform(&matrix);
	_sprite->Draw(_texture, &_srcTextureRect, NULL, NULL, _textureColor);
}
void Sprite::Release()
{
	RELEASE_COM(_texture);
}
void Sprite::Reset(LPDIRECT3DDEVICE9 device3d, LPD3DXSPRITE sprite)
{
	Init(device3d, sprite);
}