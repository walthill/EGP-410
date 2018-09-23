#include <cassert>

#include "AlignSteering.h"
#include "FaceSteering.h"
#include "WanderSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


WanderSteering::WanderSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering(), mFaceSteering(ownerID, targetLoc, targetID, shouldFlee)
{
	mType = WANDER;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);

	mWanderFacing = 0;
	mTargetFacing = 0;
}

Steering* WanderSteering::getSteering()
{
	Vector2D direction;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();
	
	/*if (mTargetID != INVALID_UNIT_ID) //target data
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}*/

	mWanderFacing += genRandomBinomial() * mWANDER_RATE;

	mTargetFacing = mWanderFacing + pOwner->getFacing();

	Vector2D ownerFacingVector = makeVector(pOwner->getFacing());
	ownerFacingVector.normalize();

	mTargetLoc = pOwner->getPositionComponent()->getPosition() + ownerFacingVector * mWANDER_OFFSET;//pOwner->getFacing().asVector();
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
	//convertedValue.normalize();
	return convertedValue;
}