#include "PathfinderPlayer.h"
#include "IdleState.h"
PathfinderPlayer::PathfinderPlayer(wstring name, wstring scriptName, wstring pngName) : Player(name, scriptName, pngName)
{
}

PathfinderPlayer::~PathfinderPlayer()
{
}
void PathfinderPlayer::UpdateAI()
{

}
void PathfinderPlayer::InitState()
{
	ReplaceState(eStateType::ET_ATTACK, new IdleState());
}