#pragma once
#include<d3dx9.h>
#include<map>
#include "Texture.h"
class ResourceManager
{
private:
	static ResourceManager* _instance;
public:
	static ResourceManager* GetInstance();
private:
	ResourceManager();
public:
	~ResourceManager();

private:
	std::map<LPCWSTR, Texture*> _textureMap;
public:
	Texture* LoadTexture(const LPCWSTR textureFileName);

};