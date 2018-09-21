#include <cassert>

#include "Steering.h"
#include "AlignSteering.h"
#include "ArriveSteering.h"
#include "FaceSteering.h"
#include "ArriveFace.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


ArriveFaceSteering::ArriveFaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: ArriveSteering(ownerID, targetLoc, targetID, shouldFlee), mFaceSteering(ownerID, targetLoc, targetID, shouldFlee)
{
	mType = ARRIVE_FACE;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering* ArriveFaceSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();
 	arriveSteeringData = ArriveSteering::getSteering();
	faceSteeringData = mFaceSteering.getSteering();

	if (arriveSteeringData != NULL)
		physicsData.acc = arriveSteeringData->getData().acc;
	else
		return nullptr;

	if (faceSteeringData != NULL)
		physicsData.rotAcc = faceSteeringData->getData().rotAcc;
	else
		return nullptr;
	
	this->mData = physicsData;

	return this;
}
