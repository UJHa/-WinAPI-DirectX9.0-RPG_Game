#include"Player.h"
#include"GameSystem.h"
#include"ComponentSystem.h"
#include"Map.h"
#include"MoveState.h"
Player::Player(LPCWSTR name, LPCWSTR scriptName, LPCWSTR pngName) : Character(name, scriptName, pngName)
{
	_moveTime = 0.1f;
	_componentType = eComponentType::CT_PLAYER;
}

Player::~Player()
{
}
void Player::UpdateAI()
{
	eDirection direction = eDirection::NONE;
	if (GameSystem::GetInstance()->IsKeyDown(VK_UP))
		direction = eDirection::UP;
	if (GameSystem::GetInstance()->IsKeyDown(VK_DOWN))
		direction = eDirection::DOWN;
	if (GameSystem::GetInstance()->IsKeyDown(VK_LEFT))
		direction = eDirection::LEFT;
	if (GameSystem::GetInstance()->IsKeyDown(VK_RIGHT))
		direction = eDirection::RIGHT;

	if (eDirection::NONE != direction)
	{
		_currentDirection = direction;
		//_state->Start();
		ChangeState(ET_MOVE);
	}
}