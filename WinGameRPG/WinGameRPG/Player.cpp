#include"Player.h"
Player::Player(LPCWSTR name) : Character(name)
{
}

Player::~Player()
{
}
void Player::UpdateAI()
{
	if (false == _isMoving)
	{
		int direction = rand() % 4;
		MoveStart((eDirection)direction);
	}
}