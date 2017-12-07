#include "StageLoader.h"
#include "LifeNPC.h"
#include "Stage.h"
#include "LifePlayer.h"
StageLoader::StageLoader(Stage* stage)
{
	_lifeNpcCount = 0;
	_stage = stage;
}

StageLoader::~StageLoader()
{
}
void StageLoader::SetName(wstring componentName)
{
	WCHAR wname[256];
	wsprintf(wname, componentName.c_str(), _lifeNpcCount);
	_name = wname;
}