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

Steering* AlignSteering::getSteering()
{
	float rotation, rotationSize, convertRotation, targetRotation;
	Vector2D direction;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();

	//get angle to target
	rotation = mTargetFacing - pOwner->getFacing();
	
	convertRotation = mapToRange(rotation);
	rotationSize = abs(convertRotation); 

	if (rotationSize < mTARGET_RADIUS)
	{
		physicsData.rotAcc = 0;
		this->mData = physicsData;
		return this;
	}
	if (rotationSize > mSLOW_RADIUS)
		targetRotation = pOwner->getMaxRotAcc();
	else
		targetRotation = pOwner->getMaxRotAcc() * rotationSize / mSLOW_RADIUS;

	targetRotation *= rotation / rotationSize;

	physicsData.rotAcc = targetRotation - physicsData.rotVel;
	physicsData.rotAcc /= mTIME_TO_TARGET;

	//clamp acceleration
	float angularAcceleration = abs(physicsData.rotAcc);
	if (angularAcceleration > physicsData.maxRotAcc) 
	{
		physicsData.rotAcc /= angularAcceleration;
		physicsData.rotAcc *= physicsData.maxRotAcc;
	}

	this->mData = physicsData;

	return this;
}

float AlignSteering::mapToRange(float rotationInRadians)
{
	float convertedRotation;

	convertedRotation = fmod((rotationInRadians), mTWO_PI);
	if (convertedRotation > PI)
		convertedRotation = (convertedRotation - PI) * -1.0f;
	else if (convertedRotation < -PI)
		convertedRotation = (convertedRotation + PI) * -1.0f;

	return convertedRotation;
}
