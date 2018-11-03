#include "component steering/Steering.h"
#include "component steering/Unit.h"
#include "component steering/UnitManager.h"
#include "PathSteering.h"

PathSteering::PathSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering()
{
	mType = PATH_STEER;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering* PathSteering::getSteering()
{
	Vector2D direction;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID); //TODO(w): change to GameApp obj
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();

	//do stuff here

	this->mData = physicsData;
	return this;
}