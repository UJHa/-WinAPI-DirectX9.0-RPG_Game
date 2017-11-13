#include "ComponentSystem.h"
#include"Component.h"
#include"Map.h"
ComponentSystem* ComponentSystem::_instance = NULL;
ComponentSystem::ComponentSystem()
{
	_componentMap.clear();
}
ComponentSystem::~ComponentSystem()
{
}
ComponentSystem* ComponentSystem::GetInstance()
{
	if (NULL == _instance)
		_instance = new ComponentSystem();
	return _instance;
}
void ComponentSystem::AddComponent(wstring name, Component* component)
{
	if (NULL != component)
	{
		map<wstring, Component*>::iterator it = _componentMap.find(name);
		if (it == _componentMap.end())
		{
			_componentMap[name] = component;
		}
	}
}
void ComponentSystem::RemoveAllComponents()
{
	for (map<wstring, Component*>::iterator it = _componentMap.begin();
		it != _componentMap.end();
		it++)
	{
		//it->second->DInit();
		delete it->second;
	}
	_componentMap.clear();
}
Component* ComponentSystem::FindComponent(LPCWSTR name)
{
	map<wstring, Component*>::iterator it = _componentMap.find(name);
	if (it != _componentMap.end())
	{
		return it->second;
	}
	return 0;
}
Component* ComponentSystem::FindComponentInRange(Component* component, int range, std::vector<eComponentType> compareTypeList)
{
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"tileMap");

	int minX = component->GetTileX() - range;
	int minY = component->GetTileY() - range;
	int maxX = component->GetTileX() + range;
	int maxY = component->GetTileY() + range;
	if (minX < 0) {
		minX = 0;
	}
	if (minY < 0) {
		minY = 0;
	}
	if (map->GetWidth() <= maxX) {
		maxX = map->GetWidth() - 1;
	}
	if (map->GetHeight() <= maxY) {
		maxY = map->GetHeight() - 1;
	}
	{
		for (int y = minY; y < maxY; y++)
		{
			for (int x = minX; x < maxX; x++)
			{
				std::list<Component*> collisionList;
				if (false == map->GetTileCollisionList(x, y, collisionList))
				{
					//collisionList ¼øÈ¯
					for (std::list<Component*>::iterator itCollision = collisionList.begin();
						itCollision != collisionList.end();
						itCollision++)
					{
						Component* component = (*itCollision);
						if (component->IsLive())
						{
							for (int i=0;i<compareTypeList.size();i++)
							{
								if (component->GetType() == compareTypeList[i])
								{
									return component;
								}
							}
						}
					}
				}
			}
		}
	}
}
void ComponentSystem::Update(float deltaTime)
{
	ProcessMessageQueue();
}
//void ComponentSystem::SendMsg(std::wstring message, Component* receiver, const sComponentMsgParam& msgParam)
void ComponentSystem::SendMsg(sComponentMsgParam& msgParam)
{
	//receiver->ReceiveMessage(message, msgParam);
	//msgParam.receiver->ReceiveMessage(msgParam);
	_msgQueue.push(msgParam);
}
void ComponentSystem::ProcessMessageQueue()
{
	while (0 < _msgQueue.size())
	{
		sComponentMsgParam msgParam = _msgQueue.front();
		_msgQueue.pop();
		msgParam.receiver->ReceiveMessage(msgParam);
	}
}