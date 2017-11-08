#include "Component.h"
#include "ComponentSystem.h"
Component::Component(LPCWSTR name)
{
	_name = name;
	ComponentSystem::GetInstance()->AddComponent(_name, this);
	_canMove = false;
	_moveDistancePerTimeX = _moveDistancePerTimeY = 0.0f;
	_componentType = eComponentType::CT_NONE;
}

Component::~Component()
{

}
void Component::ReceiveMessage(Component* sender, std::wstring message)
{
	if (L"Collision" == message)
	{

	}
}