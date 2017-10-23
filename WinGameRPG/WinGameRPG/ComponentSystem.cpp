#include "ComponentSystem.h"
#include<stdio.h>
#include"Component.h"
ComponentSystem* ComponentSystem::_instance = NULL;
ComponentSystem::ComponentSystem()
{
	
}
ComponentSystem::~ComponentSystem()
{
}
ComponentSystem* ComponentSystem::GetInstance()
{
	if (NULL == _instance)
		_instance = new ComponentSystem();
	return _instance;
}
void ComponentSystem::RemoveAllComponents()
{

}
void ComponentSystem::AddComponent(LPCWSTR name, Component* component)
{

}