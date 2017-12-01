#include "LifePlayer.h"
#include "IdleState.h"
LifePlayer::LifePlayer(wstring name, wstring scriptName, wstring pngName) : Player(name,scriptName,pngName)
{
}

LifePlayer::~LifePlayer()
{
}
void LifePlayer::InitState()
{
	Player::InitState();
	ReplaceState(eStateType::ET_ATTACK, new IdleState());
}