#include "TileCell.h"
#include "Component.h"
TileCell::TileCell(int tileX, int tileY)
{
	_posX = _posY = 0.0f;
	_componentList.clear();
	_tileX = tileX;
	_tileY = tileY;
}

TileCell::~TileCell()
{
}
void TileCell::DInit()
{
	//_sprite->DInit();
}
void TileCell::Update(float deltaTime)
{
	for (std::list<Component*>::iterator it = _renderList.begin(); it != _renderList.end(); it++)
	{
		(*it)->Update(deltaTime);
	}
}
void TileCell::Render()
{
	for (std::list<Component*>::iterator it = _renderList.begin(); it != _renderList.end(); it++)
	{
		(*it)->Render();
	}
}
void TileCell::Release()
{
	//_sprite->Release();
}
void TileCell::Reset()
{
	//_sprite->Reset();
}
float TileCell::GetPositionX()
{
	return _posX;
}
float TileCell::GetPositionY()
{
	return _posY;
}
void TileCell::AddComponent(Component* component, bool isRender)
{
	_componentList.push_back(component);

	if (isRender)
	{
		_renderList.push_back(component);
	}
}
void TileCell::RemoveComponent(Component* component)
{
	_componentList.remove(component);
	_renderList.remove(component);
}
void TileCell::MoveDeltaPosition(float deltaX, float  deltaY)
{
	_posX += deltaX;
	_posY += deltaY;
	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		(*it)->MoveDeltaPosition(deltaX, deltaY);
	}
}
void TileCell::SetPosition(float posX, float posY)
{
	_posX = posX;
	_posY = posY;
	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		(*it)->SetPosition(posX, posY);
	}
}
bool TileCell::CanMove()
{
	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		if (false == (*it)->CanMove())
			return false;
	}
	return true;
}

bool TileCell::GetCollisionList(std::list<Component*>& collisionList)
{
	for (std::list<Component*>::iterator it = _componentList.begin(); it != _componentList.end(); it++)
	{
		if (false == (*it)->CanMove())
		{
			collisionList.push_back((*it));
		}
	}
	if (0 == collisionList.size())
		return true;
	else
		return false;
}
void TileCell::InitPathfinding()
{
	_isPathfindingMark = false;
	_prePathfindingCell = NULL;
}