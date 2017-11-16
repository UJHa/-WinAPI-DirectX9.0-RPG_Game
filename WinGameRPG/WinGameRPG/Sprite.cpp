#include<fstream>
#include<reader.h>

#include"Sprite.h"
#include"GameSystem.h"
#include"Frame.h"
#include"Texture.h"
#include"ResourceManager.h"
Sprite::Sprite(LPCWSTR textureFileName, LPCWSTR scriptFileName)
	: _currentFrame(0), _frameTime(0.0f), _srcTexture(NULL),
	_textureFileName(textureFileName), _scriptFileName(scriptFileName)
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
	_srcTexture = ResourceManager::GetInstance()->LoadTexture(_textureFileName);

	//jsonTest
	{
		//파일 읽어 들여서 텍스트정보
		//텍스트 정보 파싱
		//파싱된 정보 토근 >> 의미있는 게임정보 변환
		//변환된 정보로 이용해서 Frame 생성
		std::vector<std::string> scriptTextList = ResourceManager::GetInstance()->LoadScript(_scriptFileName);
		for (int i = 0; i < scriptTextList.size();i++)
		{
			std::string record = scriptTextList[i];
			
			Json::Value root;
			Json::Reader reader;
			bool isSuccess = reader.parse(record, root);
			if (isSuccess)
			{
				std::string texture = root["texture"].asString();
				_initX = root["x"].asInt();
				_initY = root["y"].asInt();
				_width = root["width"].asInt();
				_height = root["height"].asInt();
				_delay = root["frameDelay"].asDouble();

				Frame* frame = new Frame();
				frame->Init(_srcTexture, _initX, _initY, _width, _height, _delay);
				_frameList.push_back(frame);
			}
		}
	}
	_currentFrame = 0;
	_frameTime = 0.0f;
}
void Sprite::Init(int x, int y, int width, int height, float delay)
{
	_srcTexture = ResourceManager::GetInstance()->LoadTexture(_textureFileName);
	Frame* frame = new Frame();
	frame->Init(_srcTexture, x, y, width, height, delay);
	_frameList.push_back(frame);
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
	if (_currentFrame < _frameList.size())
	{
		_frameList[_currentFrame]->SetPosition(_x, _y);
		_frameList[_currentFrame]->Render();
	}
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
		frame->Reset(_srcTexture, _initX, _initY, _width, _height, _delay);
	}
}
void Sprite::SetPosition(float x, float y)
{
	_x = x;
	_y = y;
}