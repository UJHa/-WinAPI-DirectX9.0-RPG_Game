#pragma once
#include<string>
class Component;
struct sComponentMsgParam
{
	Component* sender;
	int attackPoint;

	Component* receiver;
	std::wstring message;
};