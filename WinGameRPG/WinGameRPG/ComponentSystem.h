#pragma once
#include<Windows.h>
#include<string>
#include<map>
#include<queue>
#include<vector>
#include"sComponentMsgParam.h"
using namespace std;
class Component;
enum eComponentType;
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
	Component* FindComponent(wstring name);
	Component* FindComponentInRange(Component* map, Component* component, int range, std::vector<eComponentType> compareTypeList);
	void Update(float deltaTime);
//message
private:
	std::queue<sComponentMsgParam> _msgQueue;
public:
	void SendMsg(sComponentMsgParam& msgParam);
	void ProcessMessageQueue();
	void ClearMessageQueue();
};