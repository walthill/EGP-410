#include <cassert>

#include "AlignSteering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


FaceSteering::FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: AlignSteering(ownerID, targetLoc, targetID, shouldFlee)
{
	mType = FACE;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering* FaceSteering::getSteering()
{
	float targetFacing;
	Vector2D direction;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	
	/*if (mTargetID != INVALID_UNIT_ID) //target data
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}*/

	//get angle to target
	direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	if (direction.getLength() == 0)
		return this;

	targetFacing = atan2(direction.getY(), direction.getX());
	mTargetFacing = targetFacing;

	return AlignSteering::getSteering();
}