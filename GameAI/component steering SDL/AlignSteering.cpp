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
	float rotation, rotationSize, convertRotation, targetRotation, targetFacing;
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

	//get angle to target
	direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	targetFacing = atan2(direction.getY(), direction.getX());

	rotation = targetFacing - pOwner->getFacing();
	
	//rotation - map rotation to (-pi, pi)
	//TEST THIS
	convertRotation = fmod((rotation), mTWO_PI) - PI;
//	std::cout << convertRotation << std::endl;
	rotationSize = abs(convertRotation); //TODO: what is rotation direction?

	if (rotationSize < mTARGET_RADIUS)
		return nullptr;

	if (rotationSize > mSLOW_RADIUS)
		targetRotation = pOwner->getMaxRotAcc();
	else
		targetRotation = pOwner->getMaxRotAcc() * rotationSize / mSLOW_RADIUS;

	targetRotation *= rotation / rotationSize;

	physicsData.rotAcc = targetRotation - physicsData.rotAcc;
	physicsData.rotAcc /= mTIME_TO_TARGET;

	float angularAcceleration = abs(physicsData.rotAcc);
	if (angularAcceleration > physicsData.maxRotAcc) //normalize scalar
	{
		physicsData.rotAcc /= angularAcceleration;
		physicsData.rotAcc *= physicsData.maxRotAcc;
	}

	std::cout << physicsData.rotAcc << std::endl;
//	physicsData.acc = 0;
	this->mData = physicsData;

	return this;
}

