#include "ComponentSystem.h"
#include<stdio.h>
#include"Component.h"
ComponentSystem* ComponentSystem::_instance = NULL;
ComponentSystem::ComponentSystem()
{
	_componentMap.clear();
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
void ComponentSystem::AddComponent(wstring name, Component* component)
{
	if (NULL != component)
	{
		map<wstring, Component*>::iterator it = _componentMap.find(name);
		if (it == _componentMap.end())
		{
			_componentMap[name] = component;
		}
	}
}
void ComponentSystem::RemoveAllComponents()
{
	for (map<wstring, Component*>::iterator it = _componentMap.begin(); 
		it != _componentMap.end(); 
		it++)
	{
		delete it->second;
	}
	_componentMap.clear();
}
Component* ComponentSystem::FindComponent(LPCWSTR name)
{
	map<wstring, Component*>::iterator it = _componentMap.find(name);
	if (it != _componentMap.end())
	{
		return it->second;
	}
	return 0;
}