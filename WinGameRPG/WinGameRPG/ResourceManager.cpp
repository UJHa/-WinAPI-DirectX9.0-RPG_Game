#include"ResourceManager.h"
#include<stdio.h>
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
	std::map<LPCWSTR, Texture*>::iterator it = _textureMap.find(textureFileName);
	if (it != _textureMap.end())
	{
		return it->second;
	}
	Texture* texture = new Texture();
	texture->Init(textureFileName);

	_textureMap[textureFileName] = texture;
	return texture;
}