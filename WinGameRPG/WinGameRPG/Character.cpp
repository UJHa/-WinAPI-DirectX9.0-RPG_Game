#include "Character.h"
#include "Sprite.h"
#include "ComponentSystem.h"
#include "Map.h"
Character::Character(LPCWSTR name) : Component(name)
{
	_spriteList.clear();
}

Character::~Character()
{
}
void Character::Init()
{
	InitMove();
	WCHAR textureFileName[256];
	WCHAR scriptFileName[256];
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
		_tileX = 20;
		_tileY = 20;
		_x = map->GetPositionX(_tileX, _tileY);
		_y = map->GetPositionY(_tileX, _tileY);
		map->setTileComponent(_tileX, _tileY, this, false);
	}
}
void Character::DInit()
{
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[i]->DInit();
		delete _spriteList[i];
	}
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
void Character::MoveDeltaPosition(float deltaX, float deltaY)
{
	_x += deltaX;
	_y += deltaY;
}
void Character::InitMove()
{
	_currentDirection = eDirection::DOWN;
	_isMoving = false;
	_moveTime = 1.0f;
	_movingDuration = 0.0f;
	_targetX = 0.0f;
	_targetY = 0.0f;
	_moveDistancePerTimeX = 0.0f;
	_moveDistancePerTimeY = 0.0f;

	_deltaX = _deltaY = 0.0f;
}
void Character::MoveStart(eDirection direction)
{
	_currentDirection = direction;
	if (true == _isMoving)
		return;
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");
	map->ResetTileComponent(_tileX, _tileY, this);
	_x = map->GetPositionX(_tileX, _tileY);
	_y = map->GetPositionY(_tileX, _tileY);
	
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
		if (49 < _tileX)
			_tileX = 49;
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
		if (29 < _tileY)
			_tileY = 29;
		break;
	}
	{
		//자연스러운 이동 보간
		map->setTileComponent(_tileX, _tileY, this, true);

		//이동거리
		_targetX = map->GetPositionX(_tileX, _tileY);
		_targetY = map->GetPositionY(_tileX, _tileY);

		float distanceX = _targetX - _x;
		float distanceY = _targetY - _y;

		//최소 이동거리
		_moveDistancePerTimeX = distanceX / _moveTime;
		_moveDistancePerTimeY = distanceY / _moveTime;
	}
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
		_x = _targetX;
		_y = _targetY;
	}
	else
	{
		_movingDuration += deltaTime;

		float moveDistanceX = _moveDistancePerTimeX * deltaTime;
		float moveDistanceY = _moveDistancePerTimeY * deltaTime;

		_x += moveDistanceX;
		_y += moveDistanceY;
	}
}