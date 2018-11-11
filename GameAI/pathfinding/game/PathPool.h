#pragma once
#include "AStarPathfinder.h"
#include "DijkstraPathfinder.h"
#include "DepthFirstPathfinder.h"

class PathPool;

class PathPool
{
public:

	PathPool(const int& pathNums);
	~PathPool();

	int queryPool();
	DepthFirstPathfinder getDepthPath(int index);
	DijkstraPathfinder getDijkstraPath(int index);
	AStarPathfinder getAStarPath(int index);
	void returnPath(int index);
	void resetPathUse();

	
private:
	int mPathNums;
	
	DepthFirstPathfinder* depthPaths;
	DijkstraPathfinder* dijkstraPaths;
	AStarPathfinder* aStarPaths;
	bool mPathUse[];
};