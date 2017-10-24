#include "Component.h"
#include "ComponentSystem.h"
Component::Component(LPCWSTR name)
{
	_name = name;
	ComponentSystem::GetInstance()->AddComponent(_name, this);
}

Component::~Component()
{

}