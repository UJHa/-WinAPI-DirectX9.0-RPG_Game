#pragma once
#include "StageLoader.h"
class DefaultStageLoader : public StageLoader
{
public:
	DefaultStageLoader(Stage* stage);
	~DefaultStageLoader();

	void CreateComponents();
	Component* CreateNPC(wstring scriptName, wstring pngName);
	Component* CreateMonster(wstring scriptName, wstring pngName);
};