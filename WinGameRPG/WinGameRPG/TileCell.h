#pragma once
struct Sprite;
#include<list>
struct Component;
class TileCell
{
private:
	Sprite* _sprite;
	std::list<Component*> _componentList;
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
	void SetPosition(float posX, float posY);
	float GetPositionX();
	float GetPositionY();
	void SetSprite(Sprite* sprite);
	void AddComponent(Component* component);
	void RemoveComponent(Component* component);
};