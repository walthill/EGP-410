#pragma once

#include "DebugContent.h"

class GridPathfinder;

enum PathfindingType { DIJSKTRA_PATH, A_STAR_PATH, DEPTH_FIRST_PATH };

class PathfindingDebugContent:public DebugContent
{
public:
	PathfindingDebugContent( GridPathfinder* pPathfinder );
	~PathfindingDebugContent(){};

	void setPathfindingType(PathfindingType type) { mType = type; };
	PathfindingType getType() { return mType; };

	std::string getDebugString();

private:
	

	PathfindingType mType;
	GridPathfinder* mpPathfinder;
};