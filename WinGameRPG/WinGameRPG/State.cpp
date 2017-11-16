#include"State.h"
#include"Sprite.h"
#include"Character.h"
State::State()
{
	//_spriteList.clear();
}
State::~State()
{
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[i]->DInit();
		delete _spriteList[i];
	}
}
void State::Init(Character* character)
{
	_character = character;
	WCHAR textureFileName[256];
	wsprintf(textureFileName, L"%s.png", _character->GetTextureFileName().c_str());
	WCHAR scriptFileName[256];
	{
		wsprintf(scriptFileName, L"%s_left.json", _character->GetScriptFileName().c_str());
		Sprite* sprite = new Sprite(textureFileName, scriptFileName);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(scriptFileName, L"%s_right.json", _character->GetScriptFileName().c_str());
		Sprite* sprite = new Sprite(textureFileName, scriptFileName);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(scriptFileName, L"%s_up.json", _character->GetScriptFileName().c_str());
		Sprite* sprite = new Sprite(textureFileName, scriptFileName);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(scriptFileName, L"%s_down.json", _character->GetScriptFileName().c_str());
		Sprite* sprite = new Sprite(textureFileName, scriptFileName);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
}
void State::DInit()
{
	/*for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[i]->DInit();
		delete _spriteList[i];
	}*/
}
void State::Update(float deltaTime)
{
	_spriteList[(int)_character->GetDirection()]->Update(deltaTime);
}
void State::Start()
{
}
void State::Stop()
{

}
void State::Render()
{
	_spriteList[(int)_character->GetDirection()]->SetPosition(_character->GetX(), _character->GetY());
	_spriteList[(int)_character->GetDirection()]->Render();
}
void State::Release()
{
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[i]->Release();
	}
}
void State::Reset()
{
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[i]->Reset();
	}
}