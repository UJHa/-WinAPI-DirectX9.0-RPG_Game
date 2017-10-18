#pragma once
#include<d3dx9.h>
#include<map>
#include<fstream>
#include<vector>
#include "Texture.h"
using namespace std;
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
	map<LPCWSTR, Texture*> _textureMap;
	map<LPCWSTR, vector<string>> _scriptMap;
public:
	Texture* LoadTexture(const LPCWSTR textureFileName);
	vector<string> LoadScript(const LPCWSTR scriptFileName);

};