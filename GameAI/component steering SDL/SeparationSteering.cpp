#include <cassert>

#include "Steering.h"
#include "Game.h"
#include "SeparationSteering.h"
#include "UnitManager.h"
#include "Unit.h"

SeparationSteering::SeparationSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering()
{
	mType = SEPARATION;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering* SeparationSteering::getSteering()
{
	float distance, strength;
	Vector2D direction;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();

	for (int i = 0; i < gpGame->getUnitManager()->size(); i++)
	{	
		mTargetLoc = gpGame->getUnitManager()->getUnit(i)->getPositionComponent()->getPosition();
		direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
		distance = direction.getLength();

		if (distance < THRESHOLD)
		{
			strength = fmin(DECAY / (distance*distance), pOwner->getMaxAcc()); //inverse square

			direction.normalize();
			physicsData.acc += direction * strength;
		}
	}

	this->mData = physicsData;
	return this;
}
