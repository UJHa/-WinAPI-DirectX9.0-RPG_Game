#include "Character.h"
#include "Sprite.h"
#include "ComponentSystem.h"
#include "Map.h"
Character::Character(LPCWSTR name) : Component(name)
{
	_spriteList.clear();
	//_sprite = NULL;
}

Character::~Character()
{
}
void Character::Init()
{
	InitMove();
	WCHAR textureFileName[256];
	WCHAR scriptFileName[256];
	/*wsprintf(textureFileName, L"%s.png", _name);
	wsprintf(scriptFileName, L"%s.json", _name);
	_sprite = new Sprite(textureFileName, scriptFileName);
	_sprite->Init();*/
	{
		wsprintf(textureFileName, L"%s.png", _name);
		wsprintf(scriptFileName, L"%s_left.json", _name);
		Sprite* sprite = new Sprite(textureFileName, scriptFileName);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(textureFileName, L"%s.png", _name);
		wsprintf(scriptFileName, L"%s_right.json", _name);
		Sprite* sprite = new Sprite(textureFileName, scriptFileName);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(textureFileName, L"%s.png", _name);
		wsprintf(scriptFileName, L"%s_up.json", _name);
		Sprite* sprite = new Sprite(textureFileName, scriptFileName);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(textureFileName, L"%s.png", _name);
		wsprintf(scriptFileName, L"%s_down.json", _name);
		Sprite* sprite = new Sprite(textureFileName, scriptFileName);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
		_tileX = 7;
		_tileY = 5;
		_x = map->GetPositionX(_tileX, _tileY);
		_y = map->GetPositionY(_tileX, _tileY);
		map->setTileComponent(_tileX, _tileY, this);
	}
}
void Character::DInit()
{
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[i]->DInit();
		delete _spriteList[i];
	}
	/*if (NULL != _sprite)
	{
		_sprite->DInit();
		delete _sprite;
		_sprite = NULL;
	}*/
}
void Character::Update(float deltaTime)
{
	_spriteList[(int)_currentDirection]->Update(deltaTime);

	UpdateAI();
	UpdateMove(deltaTime);
}
void Character::Render()
{
	_spriteList[(int)_currentDirection]->SetPosition(_x, _y);
	_spriteList[(int)_currentDirection]->Render();
}
void Character::Release()
{
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[i]->Release();
	}
}
void Character::Reset()
{
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[i]->Reset();
	}
}
void Character::UpdateAI()
{
	if (false == _isMoving)
	{
		int direction = rand() % 4;
		MoveStart((eDirection)direction);
	}
}
void Character::InitMove()
{
	_currentDirection = eDirection::DOWN;
	_isMoving = false;
	_moveTime = 1.0f;
	_movingDuration = 0.0f;
}
void Character::MoveStart(eDirection direction)
{
	_currentDirection = direction;
	if (true == _isMoving)
		return;
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
	map->ResetTileComponent(_tileX, _tileY, this);

	switch (direction)
	{
	case eDirection::LEFT:
		//Left
		_tileX--;
		if (_tileX < 0)
			_tileX = 0;
		break;
	case eDirection::RIGHT:
		//Right
		_tileX++;
		if (10 < _tileX)
			_tileX = 10;
		break;
	case eDirection::UP:
		//Up
		_tileY--;
		if (_tileY < 0)
			_tileY = 0;
		break;
	case eDirection::DOWN:
		//Down
		_tileY++;
		if (10 < _tileY)
			_tileY = 10;
		break;
	}
	_x = map->GetPositionX(_tileX, _tileY);
	_y = map->GetPositionY(_tileX, _tileY);
	map->setTileComponent(_tileX, _tileY, this);
	_isMoving = true;
}
void Character::UpdateMove(float deltaTime)
{
	if (false == _isMoving)
		return;
	if (_moveTime <= _movingDuration)
	{
		_movingDuration = 0.0f;
		_isMoving = false;
	}
	else
	{
		_movingDuration += deltaTime;
	}
}