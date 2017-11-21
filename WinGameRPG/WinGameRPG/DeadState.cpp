#include "DeadState.h"
#include "Character.h"
#include "Sprite.h"
DeadState::DeadState()
{
	_nowState = eStateType::ET_DEAD;
}

DeadState::~DeadState()
{
}
void DeadState::Init(Character* character)
{
	State::Init(character);
}
void DeadState::DInit()
{
	State::DInit();
}
void DeadState::Update(float deltaTime)
{
	State::Update(deltaTime);
}
void DeadState::Render()
{
	State::Render();
}
void DeadState::Release()
{
	State::Release();
}
void DeadState::Reset()
{
	State::Reset();
}

void DeadState::Start()
{
	State::Start();
}
void DeadState::Stop()
{

}
void DeadState::CreateSprite()
{
	_spriteList.clear();
	WCHAR textureFileName[256];
	wsprintf(textureFileName, L"%s.png", _character->GetTextureFileName().c_str());
	WCHAR scriptFileName[256];
	{
		wsprintf(scriptFileName, L"%s_dead_left.json", _character->GetScriptFileName().c_str());
		Sprite* sprite = new Sprite(textureFileName, scriptFileName, 1.5f);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(scriptFileName, L"%s_dead_right.json", _character->GetScriptFileName().c_str());
		Sprite* sprite = new Sprite(textureFileName, scriptFileName, 1.5f);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(scriptFileName, L"%s_dead_up.json", _character->GetScriptFileName().c_str());
		Sprite* sprite = new Sprite(textureFileName, scriptFileName, 1.5f);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(scriptFileName, L"%s_dead_down.json", _character->GetScriptFileName().c_str());
		Sprite* sprite = new Sprite(textureFileName, scriptFileName, 1.5f);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
}