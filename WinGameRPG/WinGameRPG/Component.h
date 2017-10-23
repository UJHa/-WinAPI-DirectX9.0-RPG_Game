#pragma once
#include<Windows.h>
class Component
{
protected:
	LPCWSTR _name;
public:
	Component() {}
	Component(LPCWSTR name);
	virtual ~Component();

	virtual void Init() = 0;
	virtual void DInit() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
	virtual void Reset() = 0;
};