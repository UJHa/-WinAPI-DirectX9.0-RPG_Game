#pragma once
#include "StageLoader.h"
class Stage;
class PathfinderStageLoader : public StageLoader
{
public:
	PathfinderStageLoader(Stage* stage);
	~PathfinderStageLoader();

public:
	void CreateComponents();
};