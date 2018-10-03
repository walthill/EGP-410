#include <cassert>

#include "Steering.h"
#include "Game.h"
#include "GroupAlign.h"
#include "UnitManager.h"
#include "Unit.h"

GroupAlignSteering::GroupAlignSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: AlignSteering(ownerID, targetLoc, targetID, shouldFlee)
{
	mType = GROUP_ALIGN;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering* GroupAlignSteering::getSteering()
{
	int i;
	float distance;
	Vector2D direction, centerMassLoc;
	//int closestIndex;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();
//	Steering* alignData;

	for (i = 0; i < gpGame->getUnitManager()->size(); i++)
	{
		mTargetLoc += gpGame->getUnitManager()->getUnit(i)->getPositionComponent()->getPosition();
	}

	centerMassLoc = mTargetLoc * (1.0f / (i + 1.0f));

	direction = centerMassLoc - pOwner->getPositionComponent()->getPosition();
	distance = direction.getLength();

	if (distance < THRESHOLD)
	{
		float targetOrientation = atan2(direction.getY(), direction.getX());
		mTargetFacing = targetOrientation;

		physicsData = AlignSteering::getSteering()->getData();
	}

	this->mData = physicsData;
	return this;
}
