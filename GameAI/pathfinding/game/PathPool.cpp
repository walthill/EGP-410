#include "GameApp.h"
#include "PathPool.h"
#include "GridGraph.h"
#include "AStarPathfinder.h"
#include "DijkstraPathfinder.h"
#include "DepthFirstPathfinder.h"

PathPool::PathPool(const int& pathNums):mPathNums(pathNums)
{
	
	depthPaths = new DepthFirstPathfinder[pathNums];
	dijkstraPaths = new DijkstraPathfinder[pathNums];
	aStarPaths = new AStarPathfinder[pathNums];

	mPathUse[pathNums];

	GameApp* gpGameApp = dynamic_cast<GameApp*>(gpGame);
	
	
	for(int i = 0; i < pathNums; i++)
	{
		depthPaths[i] = DepthFirstPathfinder(gpGameApp->mpGridGraph);
		dijkstraPaths[i] = DijkstraPathfinder(gpGameApp->mpGridGraph);
		aStarPaths[i] = AStarPathfinder(gpGameApp->mpGridGraph);
		mPathUse[i] = false;
	}
}

PathPool::~PathPool()
{
}

//unit stores the index
int PathPool::queryPool()
{
	for (int i = 0; i < mPathNums; i++)
	{
		if (!mPathUse[i])
		{
			mPathUse[i] = true;
			return i; //return index of available path
		}
	}
	return -1; //not yet, amigo!
}

DepthFirstPathfinder PathPool::getDepthPath(int index)
{
		return depthPaths[index];
}
DijkstraPathfinder PathPool::getDijkstraPath(int index)
{
	return dijkstraPaths[index];
}
AStarPathfinder PathPool::getAStarPath(int index)
{
	return aStarPaths[index];
}


void PathPool::returnPath(int index)
{
	// undo pointer first
	mPathUse[index] = false;
}

void PathPool::resetPathUse()
{
	for (int i = 0; i < mPathNums; i++)
	{
		mPathUse[i] = false;
	}
}
