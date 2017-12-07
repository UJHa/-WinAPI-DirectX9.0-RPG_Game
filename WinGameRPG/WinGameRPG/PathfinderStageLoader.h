#pragma once
#include "Unit.h"
class Stage;
class PathfinderStageLoader : public Unit
{
public:
	PathfinderStageLoader(Stage* stage);
	~PathfinderStageLoader();

public:
	void CreateComponents();
};