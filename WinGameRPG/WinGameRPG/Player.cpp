#include"Player.h"
#include"GameSystem.h"
#include"ComponentSystem.h"
#include"Map.h"
Player::Player(LPCWSTR name, LPCWSTR scriptName, LPCWSTR pngName) : Character(name, scriptName, pngName)
{
	_moveTime = 1.0f;
	_componentType = eComponentType::CT_PLAYER;
}

Player::~Player()
{
}
void Player::UpdateAI()
{
	if (false == _isMoving)
	{
		if (GameSystem::GetInstance()->IsKeyDown(VK_UP))
			MoveStart(eDirection::UP);
		if (GameSystem::GetInstance()->IsKeyDown(VK_DOWN))
			MoveStart(eDirection::DOWN);
		if (GameSystem::GetInstance()->IsKeyDown(VK_LEFT))
			MoveStart(eDirection::LEFT);
		if (GameSystem::GetInstance()->IsKeyDown(VK_RIGHT))
			MoveStart(eDirection::RIGHT);
	}
}