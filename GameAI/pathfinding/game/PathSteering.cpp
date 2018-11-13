#include "GameApp.h"
#include "component steering/Steering.h"
#include "component steering/ArriveSteering.h"
#include "component steering/Unit.h"
#include "component steering/UnitManager.h"
#include "PathSteering.h"
#include "Path.h"
#include "AStarPathfinder.h"

PathSteering::PathSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering(), mArriveSteering(ownerID, targetLoc, targetID, shouldFlee)
{
	mType = PATH_STEER;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	hasArrived = false;
	once = true;
}

Steering* PathSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	GameApp* gpGameApp = dynamic_cast<GameApp*>(gpGame);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();
	
	//path data represented in Vector2D(x,y)
	std::vector<Vector2D> pathArr = pOwner->getPathInScreenSpace();
	toNodeId = pOwner->getDestinationNode();
	
	if (pathArr.size() > 0 && !hasArrived)
	{
		if (once)
		{
			gpGameApp->getPathPool()->returnPath(pOwner);
			once = false;
		}
		
		//calculate steering if target not reached
		if (nextLocationIndex < pOwner->getNumPathNodes()) 
		{
			Vector2D direction = pathArr[nextLocationIndex] - pOwner->getPositionComponent()->getPosition();
			float distanceToNextNode = direction.getLength();
	
			if (distanceToNextNode  < mArriveSteering.getTargetRadius())
			{
				nextLocationIndex++;
				oldToNodeId = toNodeId;
			}
			else
			{
				mArriveSteering.setTargetLoc(pathArr[nextLocationIndex]);
				physicsData = mArriveSteering.getSteering()->getData();
			}
		}
		else //arrived at final destination
		{
			hasArrived = true;
			physicsData.acc = 0;
			physicsData.vel = 0;
			this->mData = physicsData;
			return this;
		}
	}

	//reset values if new path has been set or current path reached
	if (toNodeId != oldToNodeId)
	{
		nextLocationIndex = 0;
		once = true;
		if (hasArrived)
		{
			hasArrived = false;
		}
	}

	this->mData = physicsData;
	return this;
}

