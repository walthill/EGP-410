#include "GameApp.h"
#include "../game/component steering/Unit.h"
#include "PathPool.h"
#include "GridGraph.h"
#include "AStarPathfinder.h"
#include "DijkstraPathfinder.h"
#include "DepthFirstPathfinder.h"
#include "component steering/SteeringComponent.h"

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

void PathPool::process() 
{
	boolean freePath = false;
	for (int i = 0; i < mPathNums; i++)
	{
		if (!mPathUse[i])
		{
			freePath = true;
			break;
		}
	}

	if (freePath)
	{
		queuedUnits[0]->generatePath(pointClicked);
		queuedUnits.erase(queuedUnits.front);
	}
}

//unit stores the index
int PathPool::queryPool(Unit* mOwner, Vector2D point)
{
	pointClicked = point;
	for (int i = 0; i < mPathNums; i++)
	{
		if (!mPathUse[i])
		{
			mPathUse[i] = true;
			members.insert(int(mOwner->getSteeringComponent()->getOwnerID()), i);
			return i; //return index of available path
		}
	}

	queuedUnits.push_back(mOwner);
	return -1; //not yet, amigo!
}

DepthFirstPathfinder* PathPool::getDepthPath(int index)
{
	if (index == -1)
		return NULL;
	return &depthPaths[index];
}
DijkstraPathfinder* PathPool::getDijkstraPath(int index)
{
	if (index == -1)
		return NULL;
	return &dijkstraPaths[index];
}
AStarPathfinder* PathPool::getAStarPath(int index)
{
	if (index == -1)
		return NULL;
	return &aStarPaths[index];
}


void PathPool::returnPath(Unit* mOwner)
{
	// undo pointer first
	std::map<int, int>::iterator pair = members.find(int(mOwner->getSteeringComponent()->getOwnerID()));
	if (pair != members.end) 
	{
		mPathUse[pair->second] = false;
	}
	

}

void PathPool::resetPathUse()
{
	for (int i = 0; i < mPathNums; i++)
	{
		mPathUse[i] = false;
	}
}
