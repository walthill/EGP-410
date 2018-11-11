#include "GameApp.h"
#include "component steering/Steering.h"
#include "component steering/Unit.h"
#include "component steering/UnitManager.h"
#include "PathSteering.h"
#include "Path.h"
#include "AStarPathfinder.h"

PathSteering::PathSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering(), mSeekSteering(ownerID, targetLoc, targetID, shouldFlee)
{
	mType = PATH_STEER;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	hasArrived = false;

	gameAppHandle = dynamic_cast<GameApp*>(gpGame);
}

Steering* PathSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();
	//pOwner.getPath
	//start node is at index 0
	
	std::vector<Vector2D> pathArr = pOwner->getPathInScreenSpace();
	if (pathArr.size() > 0 && !hasArrived)
	{
		if (nextLocationIndex < pOwner->getNumPathNodes()) //if not at end
		{
			Vector2D direction = pathArr[nextLocationIndex] - pOwner->getPositionComponent()->getPosition();
			float dist = direction.getLength();
	
			if (dist < 25)
			{
				nextLocationIndex++;
			}
			else
			{
				mSeekSteering.setTargetLoc(pathArr[nextLocationIndex]);
				physicsData = mSeekSteering.getSteering()->getData();
			}
		}
		else
		{
			hasArrived = true;
//			nextLocationIndex = 1;
			physicsData.acc = 0;
			physicsData.vel = 0;
			this->mData = physicsData;
			return this;
		}
	}

	if (hasArrived && nextLocationIndex != pOwner->getNumPathNodes())
	{
		hasArrived = false;
		nextLocationIndex = 1;
	}
	

	//do stuff here

	//calculate path using A*
	/*if(availaible path in pool)	//use messaging system
		path = A*.findPath
	
	if(owner near targetLocation && pathindex != path.len) //use distance function 
		pathindex++
		mSekkSteering.setTarget(path[0])
	
	physicsData = mSeekSteering.getSteering().data
*/
	this->mData = physicsData;
	return this;
}

