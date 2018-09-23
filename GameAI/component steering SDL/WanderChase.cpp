#include <cassert>

#include "AlignSteering.h"
#include "SeekSteering.h"
#include "FaceSteering.h"
#include "WanderSteering.h"
#include "WanderChase.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


WanderChaseSteering::WanderChaseSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: WanderSteering(ownerID, targetLoc, targetID, shouldFlee), mSeekSteering(ownerID, targetLoc, targetID, shouldFlee)
{
	mType = WANDER_CHASE;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);

}

Steering* WanderChaseSteering::getSteering()
{
	Vector2D direction;
	float directionToPlayer; 
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();
	
	if (mTargetID != INVALID_UNIT_ID) //updates target location
	{
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}
	
	mSteeringData = NULL;
	direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	directionToPlayer = direction.getLength();

	if (direction.getLength() < mSEEK_RADIUS)
	{
		mSteeringData = mSeekSteering.getSteering();
		
		mFaceSteering.setTargetLoc(mTargetLoc);
		mFaceSteeringData = mFaceSteering.getSteering();

		physicsData.rotAcc = mFaceSteeringData->getData().rotAcc;
	}
	else
	{
		mSteeringData = WanderSteering::getSteering();
		physicsData.rotAcc = mSteeringData->getData().rotAcc; 
	}
	
	physicsData.acc = mSteeringData->getData().acc;

	this->mData = physicsData;
	return this;
}
