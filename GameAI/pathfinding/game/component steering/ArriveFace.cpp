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

Steering* ArriveFaceSteering::getSteering() //TODO: rotates to slow? bigger issue?
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();
 	mArriveSteeringData = ArriveSteering::getSteering();
	mFaceSteeringData = mFaceSteering.getSteering();

	//set rotation only when arrive data is used
	if (mArriveSteeringData != NULL)
	{
		physicsData.acc = mArriveSteeringData->getData().acc;
		if(mFaceSteeringData != NULL)
			physicsData.rotAcc = mFaceSteeringData->getData().rotAcc;
	}
	else
	{
		physicsData.acc = 0;
		physicsData.vel = 0;
		physicsData.rotAcc = 0;
		physicsData.rotVel = 0;
	}
	
	this->mData = physicsData;

	return this;
}
