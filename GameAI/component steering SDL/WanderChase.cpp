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

//	mWanderFacing = 0;
//	mTargetFacing = 0;
}

Steering* WanderChaseSteering::getSteering()
{
	Vector2D direction;
	float directionToPlayer; 
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();
	//mSeekSteeringData = mSeekSteering.getSteering();
	//mWanderSteeringData = WanderSteering::getSteering();

	/*
	if(distanceToTarget < 300)
	{
		mTargetLoc = playerLoc;
		steering* newsteering = mpSeekSteering->getsteering;
		data = newsteering->getData();
	}
	else
	{

	}
	/**/

	mSteeringData = NULL;
	direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	directionToPlayer = direction.getLength();

	if (mTargetID == INVALID_UNIT_ID && directionToPlayer < mSEEK_RADIUS)
	{
		mSeekSteering.setTargetLoc(mTargetLoc);
		mSteeringData = mSeekSteering.getSteering();
		
		mFaceSteering.setTargetLoc(mTargetLoc);
		mFaceSteeringData = mFaceSteering.getSteering();
		
		if(mFaceSteeringData != NULL)
			physicsData.rotAcc = mFaceSteering.getSteering()->getData().rotAcc;
	}
	else
	{
		mSteeringData = WanderSteering::getSteering();
	
		if(mSteeringData != NULL)
			physicsData.rotAcc = mSteeringData->getData().rotAcc; 
	}
	
	physicsData.acc = mSteeringData->getData().acc;


	this->mData = physicsData;
	return this;
}


Vector2D WanderChaseSteering::makeVector(float radiansToConvert)
{
	Vector2D convertedValue;
	convertedValue.setX(cos(radiansToConvert));
	convertedValue.setY(sin(radiansToConvert));
	//convertedValue.normalize();
	return convertedValue;
}