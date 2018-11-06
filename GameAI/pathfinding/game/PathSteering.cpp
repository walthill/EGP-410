#include "Game.h"
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
}

Steering* PathSteering::getSteering()
{
	Vector2D direction;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();
	Path path;

	//do stuff here

	//calculate path using A*
	if(availaible path in pool)	//use messaging system
		path = A*.findPath
	
	if(owner near targetLocation && pathindex != path.len) //use distance function 
		pathindex++
		mSekkSteering.setTarget(path[0])

	physicsData = mSeekSteering.getSteering().data

	this->mData = physicsData;
	return this;
}