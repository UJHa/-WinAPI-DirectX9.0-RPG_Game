#include"ResourceManager.h"
ResourceManager* ResourceManager::_instance = NULL;
ResourceManager* ResourceManager::GetInstance()
{
	if (NULL == _instance)
		_instance = new ResourceManager();
	return _instance;
}
ResourceManager::ResourceManager()
{
}
ResourceManager::~ResourceManager()
{
}
Texture* ResourceManager::LoadTexture(const LPCWSTR textureFileName)
{
	map<LPCWSTR, Texture*>::iterator it = _textureMap.find(textureFileName);
	if (it != _textureMap.end())
	{
		return it->second;
	}
	Texture* texture = new Texture();
	texture->Init(textureFileName);

	_textureMap[textureFileName] = texture;
	return texture;
}
vector<string> ResourceManager::LoadScript(const LPCWSTR scriptFileName)
{
	map<LPCWSTR, vector<string>>::iterator it = _scriptMap.find(scriptFileName);
	if (it != _scriptMap.end())
	{
		return it->second;
	}
	
	vector<string> scriptTextList;
	char record[1000];
	ifstream infile(scriptFileName);
	while (!infile.eof())
	{
		infile.getline(record,100);
		scriptTextList.push_back(record);
	}

	_scriptMap[scriptFileName] = scriptTextList;
	return scriptTextList;
}