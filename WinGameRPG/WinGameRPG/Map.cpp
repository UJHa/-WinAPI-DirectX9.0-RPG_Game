#include"Map.h"
#include "Sprite.h"
#include<fstream>
Map::Map(LPCWSTR fileName)
{
	_startX = _startY = _deltaX = _deltaY = 0.0f;

	_spriteList.clear();
}
Map::~Map()
{

}
void Map::Init()
{
	//32x32 크기 타일
	//512x512에서 크기를 나눈 갯수의 타일 생성

	int srcX = 0;
	int srcY = 0;
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			Sprite* sprite = new Sprite(L"MapSprite.png", L"MapSprite.json");
			sprite->Init(srcX, srcY, 32, 32, 1.0f);
			_spriteList.push_back(sprite);
			srcX += 32;
		}
		srcX = 0;
		srcY += 32;
	}

	int index = 0;
	/*_width = 16;
	_height = 16;*/
	{
		//Load Script
		char record[1000];
		int line = 0;

		std::ifstream infile("MapData.csv");
		while (!infile.eof())
		{
			infile.getline(record, 100);

			char* token = strtok(record, ",");
			switch (line)
			{
			case 0:
				if (NULL != token)
				{
					token = strtok(NULL, ",");
					_width = atoi(token);
					token = strtok(NULL, ",");
					_height = atoi(token);
				}
				break;
			case 1:
				break;
			default:
				//map data read
				break;
			}
			line++;
		}
	}
	for (int y = 0; y < _height; y++)
	{
		std::vector<Sprite*> rowList;
		for (int x = 0; x < _width; x++)
		{
			rowList.push_back(_spriteList[index]);
			//int randValue = rand() % _spriteList.size();
			//_tileMap[y][x] = _spriteList[index];
			index++;
		}
		_tileMap.push_back(rowList);
	}
	/*for (int y = 0; y < MAP_HEIGHT; y++)
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
			_tileMap[y][x] = sprite;
		}
	}*/
}
void Map::DInit()
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->DInit();
			delete _tileMap[y][x];
		}
	}
}
void Map::Update(int deltaTime)
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->Update(deltaTime);
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
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->SetPosition(posX, posY);
			_tileMap[y][x]->Render();
			posX += tileSize;
		}
		posX = _startX;
		posY += tileSize;
	}
}
void Map::Release()
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->Release();
		}
	}
}
void Map::Reset()
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->Reset();
		}
	}
}
void Map::Scroll(float moveX, float moveY)
{
	_deltaX = moveX;
	_deltaY = moveY;
}