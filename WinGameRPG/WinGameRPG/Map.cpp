#include"Map.h"
#include "Sprite.h"
Map::Map(LPCWSTR fileName)
{
	_startX = _startY = _deltaX = _deltaY = 0.0f;
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			_testTileMap[y][x] = NULL;
		}
	}
}
Map::~Map()
{

}
void Map::Init()
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			Sprite* sprite;
			int randValue = rand() % 4;
			switch (randValue)
			{
			case 0:
				sprite = new Sprite(L"character_sprite.png", L"char_sprite_01.json");
				break;
			case 1:
				sprite = new Sprite(L"character_sprite.png", L"char_sprite_02.json");
				break;
			case 2:
				sprite = new Sprite(L"character_sprite.png", L"char_sprite_03.json");
				break;
			case 3:
				sprite = new Sprite(L"character_sprite.png", L"char_sprite_04.json");
				break;
			default:
				break;
			}
			sprite->Init();
			_testTileMap[y][x] = sprite;
		}
	}
}
void Map::DInit()
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			_testTileMap[y][x]->DInit();
			delete _testTileMap[y][x];
		}
	}
}
void Map::Update(int deltaTime)
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			_testTileMap[y][x]->Update(deltaTime);
		}
	}
}
void Map::render()
{
	int tileSize = 32;
	_startX += _deltaX;// +tileSize / 2;
	_startY += _deltaY;// +tileSize / 2;
	float posX = _startX;
	float posY = _startY;
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			_testTileMap[y][x]->SetPosition(posX, posY);
			_testTileMap[y][x]->Render();
			posX += tileSize;
		}
		posX = _startX;
		posY += tileSize;
	}
}
void Map::Release()
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			_testTileMap[y][x]->Release();
		}
	}
}
void Map::Reset()
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			_testTileMap[y][x]->Reset();
		}
	}
}
void Map::Scroll(float moveX, float moveY)
{
	_deltaX = moveX;
	_deltaY = moveY;
}