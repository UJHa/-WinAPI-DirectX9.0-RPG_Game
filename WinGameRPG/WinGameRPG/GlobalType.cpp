#include "GlobalType.h"
#include "GameSystem.h"
#include "Stage.h"
#include "Map.h"
TilePosition GetNextTilePosition(TilePosition currentTilePos, eDirection direction)
{
	TilePosition tilePosition = currentTilePos;
	switch (direction)
	{
	case eDirection::LEFT:
		tilePosition.x--;
		break;
	case eDirection::RIGHT:
		tilePosition.x++;
		break;
	case eDirection::UP:
		tilePosition.y--;
		break;
	case eDirection::DOWN:
		tilePosition.y++;
		break;
	}
	if (tilePosition.x < 0)
		tilePosition.x = 0;
	if (tilePosition.y < 0)
		tilePosition.y = 0;
	if (GameSystem::GetInstance()->GetStage()->GetMap()->GetWidth() <= tilePosition.x)
		tilePosition.x--;
	if (GameSystem::GetInstance()->GetStage()->GetMap()->GetHeight() <= tilePosition.y)
		tilePosition.y--;
	return tilePosition;
}
eDirection GetDirection(TilePosition to, TilePosition from)
{
	to.x;
	to.y;
	from.x;
	from.y;
	if (from.x < to.x)
	{
		return eDirection::RIGHT;
	}
	else if (from.x > to.x)
	{
		return eDirection::LEFT;
	}
	else if (from.y < to.y)
	{
		return eDirection::DOWN;
	}
	else if (from.y > to.y)
	{
		return eDirection::UP;
	}
	else
	{
		return eDirection::NONE;
	}
}