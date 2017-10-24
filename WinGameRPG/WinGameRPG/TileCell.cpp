#include "TileCell.h"
#include "Sprite.h"
#include "Component.h"
TileCell::TileCell()
{
	_posX = _posY = 0.0f;
	_componentList.clear();
}

TileCell::~TileCell()
{
}
void TileCell::DInit()
{
	_sprite->DInit();
}
void TileCell::Update(float deltaTime)
{
	_sprite->Update(deltaTime);
}
void TileCell::Render()
{
	_sprite->Render();

	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		(*it)->Render();
	}
}
void TileCell::Release()
{
	_sprite->Release();
}
void TileCell::Reset()
{
	_sprite->Reset();
}
void TileCell::SetPosition(float posX, float posY)
{
	_posX = posX;
	_posY = posY;
	_sprite->SetPosition(_posX, _posY);
}
float TileCell::GetPositionX()
{
	return _posX;
}
float TileCell::GetPositionY()
{
	return _posY;
}
void TileCell::SetSprite(Sprite* sprite)
{
	_sprite = sprite;
}
void TileCell::AddComponent(Component* component)
{
	_componentList.push_back(component);
}
void TileCell::RemoveComponent(Component* component)
{
	_componentList.remove(component);
}