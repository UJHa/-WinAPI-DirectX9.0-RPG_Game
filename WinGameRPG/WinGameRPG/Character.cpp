#include "Character.h"
#include "Sprite.h"

Character::Character(LPCWSTR name) : Component(name)
{
	_sprite = NULL;
}

Character::~Character()
{
}
void Character::Init()
{
	WCHAR textureFileName[256];
	WCHAR scriptFileName[256];
	wsprintf(textureFileName, L"%s.png", _name);
	wsprintf(scriptFileName, L"%s.json", _name);
	_sprite = new Sprite(textureFileName, scriptFileName);
	_sprite->Init();

	{
		//_x = _y = 100.0f;
		int mapTileSize = 32;
		int tileX = 1;
		int tileY = 1;

		_x = tileX * mapTileSize;
		_y = tileY * mapTileSize;
	}
}
void Character::DInit()
{
	if (NULL != _sprite)
	{
		_sprite->DInit();
		delete _sprite;
		_sprite = NULL;
	}
}
void Character::Update(float deltaTime)
{
	_sprite->Update(deltaTime);
}
void Character::Render()
{
	_sprite->SetPosition(_x, _y);
	_sprite->Render();
}
void Character::Release()
{
	_sprite->Release();
}
void Character::Reset()
{
	_sprite->Reset();
}