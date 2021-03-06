#include <cassert>

#include "AlignSteering.h"
#include "FaceSteering.h"
#include "WanderSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


WanderSteering::WanderSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee)
	: Steering(), mFaceSteering(ownerID, targetLoc, targetID, shouldFlee)
{
	mType = WANDER;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);

	mWanderFacing = 0;
	mTargetFacing = 0;
}

Steering* WanderSteering::getSteering(std::vector<Unit*> unitList)
{
	return getSteering(); //called in flock steering
}

Steering* WanderSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();
	
	mWanderFacing += genRandomBinomial() * mWANDER_RATE;

	mTargetFacing = mWanderFacing + pOwner->getFacing();

	Vector2D ownerFacingVector = makeVector(pOwner->getFacing());
	ownerFacingVector.normalize();

	mTargetLoc = pOwner->getPositionComponent()->getPosition() + ownerFacingVector * mWANDER_OFFSET;
	mTargetLoc += makeVector(mTargetFacing) * mWANDER_RADIUS;
	mFaceSteering.setTargetLoc(mTargetLoc);

	Steering* faceData = mFaceSteering.getSteering();
	
	if(faceData != NULL) 
		physicsData.rotAcc = faceData->getData().rotAcc;

	physicsData.acc = ownerFacingVector * pOwner->getMaxAcc();

	this->mData = physicsData;
	return this;
}


Vector2D WanderSteering::makeVector(float radiansToConvert)
{
	Vector2D convertedValue;
	convertedValue.setX(cos(radiansToConvert));
	convertedValue.setY(sin(radiansToConvert));
	return convertedValue;
}