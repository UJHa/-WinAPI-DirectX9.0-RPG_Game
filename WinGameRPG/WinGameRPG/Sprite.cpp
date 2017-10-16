#include<fstream>
#include<reader.h>

#include"Sprite.h"
#include"GameSystem.h"
#include"Frame.h"
#include"Texture.h"
#include"ResourceManager.h"
Sprite::Sprite() : _currentFrame(0), _frameTime(0.0f), _srcTexture(NULL)
{
}

Sprite::~Sprite()
{
	if (NULL != _srcTexture)
	{
		_srcTexture->DInit();
		delete _srcTexture;
		_srcTexture = NULL;
	}
}
void Sprite::Init()
{
	/*_srcTexture = new Texture();
	_srcTexture->Init(L"character_sprite.png");*/
	_srcTexture = ResourceManager::GetInstance()->LoadTexture(L"character_sprite.png");

	//jsonTest
	{
		//파일 읽어 들여서 텍스트정보
		//텍스트 정보 파싱
		//파싱된 정보 토근 >> 의미있는 게임정보 변환
		//변환된 정보로 이용해서 Frame 생성
		char inputBuffer[1000];
		std::ifstream infile("jsonText.json");
		while (!infile.eof())
		{
			infile.getline(inputBuffer,100);
			
			Json::Value root;
			Json::Reader reader;
			bool isSuccess = reader.parse(inputBuffer, root);
			while (isSuccess)
			{
				std::string texture = root["texture"].asString();
				int x = root["width"].asInt();
				int y = root["y"].asInt();
			}
		}
	}

	////Texture
	//{
	//	//파일로 이미지 폭과 너비를 가져온다.
	//	HRESULT hr = D3DXGetImageInfoFromFile(L"character_sprite.png", &_textureInfo);
	//	if (FAILED(hr))
	//	{
	//		MessageBox(0, L"D3DXGetImageInfoFromFile 에러입니다.", L"ErrorMessage", 0);
	//		return;
	//	}
	//	//텍스쳐 생성
	//	hr = D3DXCreateTextureFromFileEx(
	//		GameSystem::GetInstance()->GetDevice3d(),
	//		L"character_sprite.png",
	//		_textureInfo.Width,
	//		_textureInfo.Height,
	//		0, 0,
	//		D3DFMT_UNKNOWN,
	//		D3DPOOL_DEFAULT,
	//		D3DX_DEFAULT,
	//		D3DX_DEFAULT,
	//		D3DCOLOR_ARGB(255, 255, 255, 255),
	//		&_textureInfo,
	//		NULL,
	//		&_texture
	//	);
		{
			Frame* frame = new Frame();
			frame->Init(_srcTexture, 32 * 0, 0, 32, 32, 0.2f);
			_frameList.push_back(frame);
		}
		{
			Frame* frame = new Frame();
			frame->Init(_srcTexture, 32 * 2, 0, 32, 32, 0.2f);
			_frameList.push_back(frame);
		}
	//}
	_currentFrame = 0;
	_frameTime = 0.0f;
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
	_srcTexture->DInit();
}
void Sprite::Update(float deltaTime)
{
	_frameTime += deltaTime;
	if (_frameList[_currentFrame]->GetFrameDelay() <= _frameTime)
	{
		_frameTime = 0.0f;
		_currentFrame = (_currentFrame + 1) % _frameList.size();
	}
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
	_srcTexture->Release();
}
void Sprite::Reset()
{
	Init();
	for (std::vector<Frame*>::iterator it = _frameList.begin(); it != _frameList.end(); it++)
	{
		Frame* frame = *it;
		frame->Reset();
	}
}