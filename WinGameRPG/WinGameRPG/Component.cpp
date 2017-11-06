#include "Component.h"
#include "ComponentSystem.h"
Component::Component(LPCWSTR name)
{
	_name = name;
	ComponentSystem::GetInstance()->AddComponent(_name, this);
	_canMove = false;
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