#include "PathfinderPlayer.h"
#include "IdleState.h"
#include "PathfindingState.h"
#include "PathFindingMoveState.h"
PathfinderPlayer::PathfinderPlayer(wstring name, wstring scriptName, wstring pngName) : Player(name, scriptName, pngName)
{
	_moveTime = 1.0f;
}

PathfinderPlayer::~PathfinderPlayer()
{
}
void PathfinderPlayer::UpdateAI()
{

}
void PathfinderPlayer::InitState()
{
	Player::InitState();
	ReplaceState(eStateType::ET_MOVE, new PathFindingMoveState());
	//ReplaceState(eStateType::ET_ATTACK, new IdleState());
	ReplaceState(eStateType::ET_PATHFINDING, new PathfindingState());
}