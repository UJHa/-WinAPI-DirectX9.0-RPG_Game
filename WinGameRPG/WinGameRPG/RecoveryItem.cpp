#include"RecoveryItem.h"
#include"ComponentSystem.h"
#include"Sprite.h"
#include"Map.h"
#include"Character.h"
RecoveryItem::RecoveryItem(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textureFileName) : Component(name)
{
	_componentType = eComponentType::CT_ITEM;
	_sprite = NULL;
	_scriptName = scriptName;
	_textureFileName = textureFileName;

	_posX = _posY = 0.0f;
}

RecoveryItem::~RecoveryItem()
{

}
void RecoveryItem::Init()
{
	{
		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
		_tileX = rand() % map->GetWidth();
		_tileY = rand() % map->GetHeight();
		while (!map->CanMoveTileMap(_tileX, _tileY))
		{
			_tileX = rand() % map->GetWidth();
			_tileY = rand() % map->GetHeight();
		}
		_posX = map->GetPositionX(_tileX, _tileY);
		_posY = map->GetPositionY(_tileX, _tileY);
		map->setTileComponent(_tileX, _tileY, this, true);
	}
	WCHAR textureFileName[256];
	wsprintf(textureFileName, L"%s.png", _textureFileName.c_str());
	WCHAR scriptFileName[256];
	{	
		wsprintf(scriptFileName, L"%s.json", _scriptName.c_str());
		_sprite = new Sprite(textureFileName, scriptFileName);
		_sprite->Init();
	}
	_canMove = true;
}
void RecoveryItem::DInit()
{
	_sprite->DInit();
}
void RecoveryItem::Update(float deltaTime)
{
	if (false == _isLive)
		return;
	_sprite->Update(deltaTime);
}
void RecoveryItem::Render()
{
	if (false == _isLive)
		return;
	_sprite->SetPosition(_posX, _posY);
	_sprite->Render();
}
void RecoveryItem::Release()
{
	_sprite->Release();
}
void RecoveryItem::Reset()
{
	_sprite->Reset();
}
void RecoveryItem::MoveDeltaPosition(float deltaX, float deltaY)
{
	_posX += deltaX;
	_posY += deltaY;
	_sprite->SetPosition(_posX, _posY);
}
void RecoveryItem::SetPosition(float posX, float posY)
{
	_posX = posX;
	_posY = posY;
}
void RecoveryItem::ReceiveMessage(const sComponentMsgParam msgParam)
{
	if (L"Use" == msgParam.message)
	{
		Component* sender = msgParam.sender;
		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
		switch (sender->GetType())
		{
		case eComponentType::CT_NPC:
		case eComponentType::CT_MONSTER:
		case eComponentType::CT_PLAYER:
			((Character*)sender)->IncreaseHP(50);
			//((Character*)sender)->DecreaseHP(50);
			map->ResetTileComponent(msgParam.sender->GetTileX(), sender->GetTileY(), msgParam.receiver);
			_isLive = false;
			break;
		}
	}
}