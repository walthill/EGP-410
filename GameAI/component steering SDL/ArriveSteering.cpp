#include <cassert>

#include "Steering.h"
#include "ArriveSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


ArriveSteering::ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering()
{
	if (shouldFlee)
		mType = FLEE;
	else
		mType = ARRIVE;
	
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering* ArriveSteering::getSteering()
{
	float targetSpeed, distance;
	Vector2D direction, targetVelocity;

	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();

	if (mTargetID != INVALID_UNIT_ID) //target data
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	if(mType == ARRIVE || mType == ARRIVE_FACE)
		direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	else
		direction = pOwner->getPositionComponent()->getPosition() - mTargetLoc;

	distance = direction.getLength();

	if (distance < mTARGET_RADIUS) //check if arrived
		return nullptr;

	if (distance > mSLOW_RADIUS) //if outside zone go max speed
		targetSpeed = pOwner->getMaxSpeed();
	else					    //if inside, scale speed
		targetSpeed = pOwner->getMaxSpeed() * distance / mSLOW_RADIUS;

	//combine speed and direction
	targetVelocity = direction; 
	targetVelocity.normalize();
	targetVelocity *= targetSpeed;

	//need char velocity
	physicsData.acc = targetVelocity - physicsData.vel;
	physicsData.acc /= mTIME_TO_TARGET;

//	pOwner->getPhysicsComponent()->setData()

	//clamp acceleration
	if (physicsData.acc.getLengthSquared() > pOwner->getMaxAcc()*pOwner->getMaxAcc())
	{
		physicsData.acc.normalize();
		physicsData.acc *= pOwner->getMaxAcc();
	}

//	this->mData.rotVel = 0;
	this->mData = physicsData;
//	this->mData.rotAcc = 0;
//	pOwner->getPhysicsComponent()->setData();

	return this;
}

	