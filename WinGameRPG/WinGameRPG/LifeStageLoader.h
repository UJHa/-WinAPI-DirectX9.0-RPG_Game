#pragma once
#include "StageLoader.h"
class LifeStageLoader : public StageLoader
{
public:
	LifeStageLoader(Stage* stage);
	~LifeStageLoader();

	void CreateComponents();
	Component* CreateLifeNPC(wstring scriptName, wstring pngName);
};