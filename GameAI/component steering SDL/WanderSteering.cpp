#include <cassert>

#include "AlignSteering.h"
#include "FaceSteering.h"
#include "WanderSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


WanderSteering::WanderSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: FaceSteering(ownerID, targetLoc, targetID, shouldFlee)
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

	if (mTargetID != INVALID_UNIT_ID) //target data
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	mWanderFacing += genRandomBinomial() * mWANDER_RATE;

	mTargetFacing = mWanderFacing + pOwner->getFacing();

	Vector2D ownerFacingVector = makeVector(pOwner->getFacing());
	mTargetLoc = pOwner->getPositionComponent()->getPosition() + mWANDER_OFFSET * ownerFacingVector.getLength();//pOwner->getFacing().asVector();

	mTargetLoc += mWANDER_RADIUS * makeVector(mTargetFacing).getLength();

	FaceSteering::getSteering();

	physicsData.acc = pOwner->getPhysicsComponent()->getData().maxAccMagnitude * ownerFacingVector.getLength();

	this->mData = physicsData;
	return this;
}


Vector2D WanderSteering::makeVector(float radiansToConvert)
{
	Vector2D convertedValue;
	convertedValue.setX(cosf(radiansToConvert));
	convertedValue.setY(sinf(radiansToConvert));
	convertedValue.normalize();
	return convertedValue;
}