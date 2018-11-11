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

	int queryPool(Unit* mOwner, Vector2D point);
	DepthFirstPathfinder* getDepthPath(int index);
	DijkstraPathfinder* getDijkstraPath(int index);
	AStarPathfinder* getAStarPath(int index);
	void returnPath(Unit* mOwner);
	void resetPathUse();
	void process();

	
private:
	int mPathNums;

	std::vector<Unit*> queuedUnits;
	Vector2D pointClicked;
	std::map<int, int> members;

	DepthFirstPathfinder* depthPaths;
	DijkstraPathfinder* dijkstraPaths;
	AStarPathfinder* aStarPaths;
	bool mPathUse[];
};