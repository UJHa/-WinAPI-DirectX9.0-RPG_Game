#include"Sprite.h"
#include"GameSystem.h"
#include"Frame.h"
Sprite::Sprite() : _currentFrame(0)
{
}

Sprite::~Sprite()
{
}
void Sprite::Init(LPDIRECT3DDEVICE9 device3d, LPD3DXSPRITE sprite)
{
	_device3d = device3d;
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
		{
			Frame* frame = new Frame();
			frame->Init(device3d, sprite, _texture, 32*0, 0, 32, 32);
			_frameList.push_back(frame);
		}
		{
			Frame* frame = new Frame();
			frame->Init(device3d, sprite, _texture, 32*1, 0, 32, 32);
			_frameList.push_back(frame);
		}
		{
			Frame* frame = new Frame();
			frame->Init(device3d, sprite, _texture, 32*2, 0, 32, 32);
			_frameList.push_back(frame);
		}
		/*for (int i = 0; i < 3; i++)
		{
			Frame* frame = new Frame();
			frame->Init(device3d, sprite, _texture, _textureInfo.Width / 3 * i, 0, _textureInfo.Width / 3 * (i+1), _textureInfo.Height / 4);
			_frameList.push_back(frame);
		}*/
	}
	_currentFrame = 1;
}
void Sprite::DInit()
{
	for (std::vector<Frame*>::iterator it = _frameList.begin(); it != _frameList.end(); it++)
	{
		Frame* frame = *it;
		frame->DInit();
		delete frame;
	}
	_frameList.clear();
	RELEASE_COM(_texture);
}
void Sprite::Render()
{
	if(_currentFrame < _frameList.size())
		_frameList[_currentFrame]->Render();
}
void Sprite::Release()
{
	for (std::vector<Frame*>::iterator it = _frameList.begin(); it != _frameList.end(); it++)
	{
		Frame* frame = *it;
		frame->Release();
	}
	RELEASE_COM(_texture);
}
void Sprite::Reset(LPDIRECT3DDEVICE9 device3d, LPD3DXSPRITE sprite)
{
	Init(device3d, sprite);
	for (std::vector<Frame*>::iterator it = _frameList.begin(); it != _frameList.end(); it++)
	{
		Frame* frame = *it;
		frame->Reset(device3d, sprite);
	}
}