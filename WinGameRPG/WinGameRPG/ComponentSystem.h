#pragma once
#include<Windows.h>
#include<string>
#include<map>
using namespace std;
struct Component;
class ComponentSystem
{
	//Sington Pattern
private:
	static ComponentSystem* _instance;
	ComponentSystem();
public:
	~ComponentSystem();
	static ComponentSystem* GetInstance();

private:
	map<wstring, Component*> _componentMap;
public:
	void AddComponent(wstring name, Component* component);
	void RemoveAllComponents();
	Component* FindComponent(LPCWSTR name);
};