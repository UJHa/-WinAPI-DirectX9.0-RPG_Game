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
	map<wstring, Texture*> _textureMap;
	map<wstring, vector<string>> _scriptMap;
public:
	Texture* LoadTexture(const wstring textureFileName);
	vector<string> LoadScript(const wstring scriptFileName);

};