#pragma once
#include<Windows.h>
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

public:
	void RemoveAllComponents();
	void AddComponent(LPCWSTR name, Component* component);
};