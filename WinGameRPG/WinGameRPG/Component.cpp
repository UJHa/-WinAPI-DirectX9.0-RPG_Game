#include "Component.h"
#include "ComponentSystem.h"
#include"sComponentMsgParam.h"
Component::Component(LPCWSTR name)
{
	_name = name;
	ComponentSystem::GetInstance()->AddComponent(_name, this);
	_canMove = false;
	_moveDistancePerTimeX = _moveDistancePerTimeY = 0.0f;
	_componentType = eComponentType::CT_NONE;
	_isLive = true;
}

Component::~Component()
{

}
void Component::ReceiveMessage(const sComponentMsgParam msgParam)
{
	if (L"Collision" == msgParam.message)
	{
	}
}