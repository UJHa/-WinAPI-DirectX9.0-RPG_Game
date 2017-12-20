#pragma once
#include "PathfindingState.h"
class PathfindingImmediateState : public PathfindingState
{
public:
	PathfindingImmediateState();
	~PathfindingImmediateState();
public:
	void Start();
};
