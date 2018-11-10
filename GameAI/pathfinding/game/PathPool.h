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
	GridPathfinder* getPath(int index, int pathType);
	void returnPath(int index);

	
private:
	int mPathNums;
	
	DepthFirstPathfinder depthPaths[];
	DijkstraPathfinder dijkstraPaths[];
	AStarPathfinder aStarPaths[];
	bool mPathUse[];
};