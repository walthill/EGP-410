#include "GameApp.h"
#include "PathPool.h"
#include "AStarPathfinder.h"
#include "DijkstraPathfinder.h"
#include "DepthFirstPathfinder.h"

PathPool::PathPool(const int& pathNums):mPathNums(pathNums)
{
	depthPaths[pathNums];
	dijkstraPaths[pathNums];
	aStarPaths[pathNums];

	mPathUse[pathNums];

	GameApp* gpGameApp = dynamic_cast<GameApp*>(gpGame);
	
	for(int i = 0; i < pathNums; i++)
	{
		depthPaths[i] = new DepthFirstPathfinder(gpGameApp->mpGridGraph);
		dijkstraPaths[i] = new DijkstraPathfinder(gpGameApp->mpGridGraph);
		aStarPaths[i] = new AStarPathfinder(gpGameApp->mpGridGraph);
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

GridPathfinder* PathPool::getPath(int index, int pathType)
{
	if(pathType = 0)
	{
		return depthPaths[index];
	}
	if (pathType = 1)
	{
		return dijkstraPaths[index];
	}
	if (pathType = 2)
	{
		return aStarPaths[index];
	}
	else
	{
		return nullptr;
	}
	
}


void PathPool::returnPath(int index)
{
	// undo pointer first
	mPathUse[index] = false;
}


