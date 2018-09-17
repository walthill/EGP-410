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
	{
		mType = Steering::FLEE;
	}
	else
	{
		mType = Steering::SEEK;
	}
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering* ArriveSteering::getSteering()
{
	//pOwner is character & pTarget is target
	float targetSpeed, distance;
	
	Vector2D direction;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData;
	//are we seeking a location or a unit?

	if (mTargetID != INVALID_UNIT_ID) //target data
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	distance = direction.getLength();

	if (distance < mTargetRadius) //check if arrived
		return nullptr;

	if (distance > mSlowRadius) //if outside zone go max speed
		targetSpeed = pOwner->getMaxSpeed();
	else					    //if inside, scale speed
		targetSpeed = pOwner->getMaxSpeed() * distance / mSlowRadius;

	//combine speed and direction
	Vector2D targetVelocity = pOwner->getFacing();
	targetVelocity.normalize();
	targetVelocity += targetSpeed;

	pOwner->getPhysicsComponent()->setData() = targetVelocity - pOwner->getPhysicsComponent()->getData().vel;
	//pOwner->getPositionComponent()->setPosition(targetVelocity - pOwner->getPositionComponent().get)

	if()

	pOwner->getPositionComponent()->setFacing = 0;

	return this;
}

