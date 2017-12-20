#include "Effect.h"
#include "Sprite.h"
#include "GameSystem.h"
#include "Stage.h"
#include "Map.h"
Effect::Effect()
{
}

Effect::~Effect()
{
}
void Effect::Init()
{
	/*WCHAR textureFileName[256];
	wsprintf(textureFileName, L"%s.png", _textureFileName.c_str());
	WCHAR scriptFileName[256];*/
	{
		//wsprintf(scriptFileName, L"%s.json", _scriptName.c_str());
		//_sprite = new Sprite(textureFileName, scriptFileName);
		_sprite = new Sprite(L"MapSprite.png", L"effect_water.json");
		_sprite->Init();
	}
	_canMove = true;
}
void Effect::DInit()
{
	_sprite->DInit();
}
void Effect::Update(float deltaTime)
{
	if (false == _isLive)
		return;
	_sprite->Update(deltaTime);
}
void Effect::Render()
{
	if (false == _isLive)
		return;
	_sprite->SetPosition(_posX, _posY);
	_sprite->Render();
}
void Effect::Release()
{
	_sprite->Release();
}
void Effect::Reset()
{
	_sprite->Reset();
}
void Effect::MoveDeltaPosition(float deltaX, float deltaY)
{
	_posX += deltaX;
	_posY += deltaY;
	_sprite->SetPosition(_posX, _posY);
}
void Effect::SetPosition(float posX, float posY) 
{
	_posX = posX;
	_posY = posY;
}
void Effect::InitTilePosition(int tileX, int tileY)
{
	Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
	map->setTileComponent(tileX, tileY, this, false);
}