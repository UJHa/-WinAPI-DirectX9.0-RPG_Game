#include"NPC.h"
NPC::NPC(LPCWSTR name) : Character(name)
{
}

NPC::~NPC()
{
}
void NPC::UpdateAI()
{
	if (false == _isMoving)
	{
		int direction = rand() % 4;
		MoveStart((eDirection)direction);
	}
}