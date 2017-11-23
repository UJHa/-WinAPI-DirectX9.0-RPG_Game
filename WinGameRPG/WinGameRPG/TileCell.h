#pragma once
//struct Sprite;
#include<list>
class Component;
class TileCell
{
private:
	//Sprite* _sprite;
	std::list<Component*> _componentList;
	std::list<Component*> _renderList;
	float _posX;
	float _posY;
public:
	TileCell();
	~TileCell();

	void DInit();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();
	float GetPositionX();
	float GetPositionY();
	void AddComponent(Component* component, bool isRender);
	void RemoveComponent(Component* component);
	void MoveDeltaPosition(float deltaX, float  deltaY);
	void SetPosition(float posX, float posY);

	bool CanMove();
	bool GetCollisionList(std::list<Component*>& collisionList);
	std::list<Component*> GetComponentList() {	return _componentList; }
};