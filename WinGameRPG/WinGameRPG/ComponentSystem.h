#pragma once
#include<Windows.h>
#include<string>
#include<map>
#include<vector>
using namespace std;
class Component;
enum eComponentType;
struct sComponentMsgParam;
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
	Component* FindComponentInRange(Component* component, int range, std::vector<eComponentType> compareTypeList);
//message
public:
	void SendMsg(std::wstring message, Component* receiver, const sComponentMsgParam& msgParam);
};