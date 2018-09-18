#include <cassert>

#include "Steering.h"
#include "AlignSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


AlignSteering::AlignSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering()
{
	mType = ALIGN;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

//TODO: integrate align into steering component
Steering* AlignSteering::getSteering()
{
	float rotation, rotationSize, convertRotation, targetRotation;

	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();

	if (mTargetID != INVALID_UNIT_ID) //target data
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
		targetRotation = pTarget->getFacing();
	}

	rotation = targetRotation - pOwner->getFacing();
	
	//rotation - map rotation to (-pi, pi)
	//TEST THIS
	convertRotation = (int)(rotation + mTWO_PI) % (int)floor(mTWO_PI);

	rotationSize = abs(rotationDirection); //TODO: what is rotation direction?

	if (rotationSize < mTARGET_RADIUS)
		return nullptr;

	if (rotationSize > mSLOW_RADIUS)
		targetRotation = pOwner->getMaxRotAcc();
	else
		targetRotation = pOwner->getMaxRotAcc() * rotationSize / mSLOW_RADIUS;

	targetRotation *= rotation / rotationSize;

	physicsData.rotAcc = targetRotation - pOwner->getPhysicsComponent()->getRotationalAcceleration();
	physicsData.rotAcc /= mTIME_TO_TARGET;

	float angularAcceleration = abs(physicsData.rotAcc);
	
	if (angularAcceleration > physicsData.maxRotAcc) //normalize scalar
	{
		physicsData.rotAcc /= angularAcceleration;
		physicsData.rotAcc *= physicsData.maxRotAcc;
	}

	physicsData.acc = 0;
	this->mData = physicsData;

	return this;
}

