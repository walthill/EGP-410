#include <cassert>

#include "AlignSteering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


FaceSteering::FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee)
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

	direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	if (direction.getLength() <= mTARGET_RADIUS)
		return this;

	targetFacing = atan2(direction.getY(), direction.getX());
	mTargetFacing = targetFacing;

	return AlignSteering::getSteering();
}