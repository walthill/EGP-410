#include <cassert>

#include "Steering.h"
#include "Game.h"
#include "SeparationSteering.h"
#include "UnitManager.h"
#include "Unit.h"

//TODO: pass in a list of targets?
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
		direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
		distance = direction.getLength();

		if (direction < THRESHOLD)
		{
			strength = fmin(DECAY / (distance*distance), pOwner->getMaxAcc()); //inverse square

			direction.normalize();
			physicsData.acc += strength * direction;
		}
	}

	this->mData = physicsData;
	return this;
}
