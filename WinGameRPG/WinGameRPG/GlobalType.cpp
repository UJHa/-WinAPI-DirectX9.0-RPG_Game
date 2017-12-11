#include "GlobalType.h"
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
	return tilePosition;
}