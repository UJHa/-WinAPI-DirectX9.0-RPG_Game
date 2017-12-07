#include "Unit.h"
#include "LifeNPC.h"
#include "Stage.h"
#include "LifePlayer.h"
Unit::Unit(Stage* stage)
{
	_lifeNpcCount = 0;
	_stage = stage;
}

Unit::~Unit()
{
}
void Unit::SetName(wstring componentName)
{
	WCHAR wname[256];
	wsprintf(wname, componentName.c_str(), _lifeNpcCount);
	_name = wname;
}