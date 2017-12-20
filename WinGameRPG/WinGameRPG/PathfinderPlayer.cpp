#include "PathfinderPlayer.h"
#include "IdleState.h"
#include "PathfindingState.h"
#include "PathFindingMoveState.h"
#include "GameSystem.h"
#include "Stage.h"
#include "Map.h"
#include "PathfindingImmediateState.h"
PathfinderPlayer::PathfinderPlayer(wstring name, wstring scriptName, wstring pngName) : Player(name, scriptName, pngName)
{
	_moveTime = 0.1f;
}

PathfinderPlayer::~PathfinderPlayer()
{
}
void PathfinderPlayer::UpdateAI()
{
	//mouse input
	if (GameSystem::GetInstance()->GetMouseDown())
	{
		int mouseX = GameSystem::GetInstance()->GetMouseX();
		int mouseY = GameSystem::GetInstance()->GetMouseY();
		TileCell* targetTileCell = GameSystem::GetInstance()->GetStage()
			->GetMap()->FindTileCellWithMousePosition(mouseX, mouseY);
		if (NULL != targetTileCell)
		{
			SetTargetTileCell(targetTileCell);
		}
	}
}
void PathfinderPlayer::InitState()
{
	Player::InitState();
	ReplaceState(eStateType::ET_MOVE, new PathFindingMoveState());
	ReplaceState(eStateType::ET_PATHFINDING, new PathfindingImmediateState());
}