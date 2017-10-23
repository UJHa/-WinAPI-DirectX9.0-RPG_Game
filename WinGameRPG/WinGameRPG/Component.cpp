#include "Component.h"
#include "ComponentSystem.h"
Component::Component(LPCWSTR name)
{
	_name = name;
	ComponentSystem::GetInstance()->AddComponent(name, this);
}

Component::~Component()
{

}