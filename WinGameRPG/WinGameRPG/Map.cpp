#include"Map.h"
#include "Sprite.h"
#include"TileCell.h"
#include<fstream>
Map::Map(LPCWSTR name) : Component(name)
{
	_startX = _startY = _deltaX = _deltaY = 0.0f;
	_tileSize = 32;
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
	{
		//Load Script
		char record[1024];
		int line = 0;

		ifstream infile("MapData.csv");
		while (!infile.eof())
		{
			infile.getline(record, 1024);

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
				if (NULL != token)
				{
					vector<TileCell*> rowList;
					for (int x = 0; x < _width; x++)
					{
						index = atoi(token);

						TileCell* tileCell = new TileCell();
						tileCell->SetSprite(_spriteList[index]);
						rowList.push_back(tileCell);
						token = strtok(NULL, ",");
					}
					_tileMap.push_back(rowList);
				}
				break;
			}
			line++;
		}
	}

	_startX += _deltaX;
	_startY += _deltaY;
	float posX = _startX;
	float posY = _startY;
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->SetPosition(posX, posY);
			_tileMap[y][x]->Render();
			posX += _tileSize;
		}
		posX = _startX;
		posY += _tileSize;
	}
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
void Map::Update(float deltaTime)
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->Update(deltaTime);
		}
	}
}
void Map::Render()
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->MoveDeltaPosition(_deltaX, _deltaY);
			_tileMap[y][x]->Render();
		}
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
int Map::GetPositionX(int tileX, int tileY)
{
	return _tileMap[tileY][tileX]->GetPositionX();
}
int Map::GetPositionY(int tileX, int tileY)
{
	return _tileMap[tileY][tileX]->GetPositionY();
}
void Map::setTileComponent(int tileX, int tileY, Component* component, bool isRender)
{
	_tileMap[tileY][tileX]->AddComponent(component, isRender);
}
void Map::ResetTileComponent(int tileX, int tileY, Component* component)
{
	_tileMap[tileY][tileX]->RemoveComponent(component);
}