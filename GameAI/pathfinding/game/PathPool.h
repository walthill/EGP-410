#pragma once

#include "Vector2D.h"
#include <vector>
#include <map>
#include "Trackable.h"

class DepthFirstPathfinder;
class DijkstraPathfinder;
class AStarPathfinder;

class PathPool:public Trackable
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
	
	DepthFirstPathfinder* depthPaths;
	DijkstraPathfinder* dijkstraPaths;
	AStarPathfinder* aStarPaths;

	
private:
	GameApp* gpGameApp;
	int mPathNums;

	std::vector<Unit*> queuedUnits;
	Vector2D pointClicked;
	std::map<int, int> members;

	
	bool* mPathUse;
};