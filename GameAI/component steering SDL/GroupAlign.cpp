#include <cassert>

#include "Steering.h"
#include "AlignSteering.h"
#include "FaceSteering.h"
#include "Game.h"
#include "GroupAlign.h"
#include "UnitManager.h"
#include "Unit.h"

GroupAlignSteering::GroupAlignSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: FaceSteering(ownerID, targetLoc, targetID, shouldFlee)
{
	mType = GROUP_ALIGN;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	unitManangerHandle = gpGame->getUnitManager();
}

Steering* GroupAlignSteering::getSteering()
{
	int neighborCount = 0;
	float distance = 0, averageRotation = 0;
	Vector2D direction, centerMassLoc;
	pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();
	unitMapSize = unitManangerHandle->size();


	//skip 0 - thats the player id
	for (int i = 1; i < unitMapSize+1; i++)
	{
		currentUnit = unitManangerHandle->getUnit(i);
	
		if (pOwner != currentUnit && currentUnit != NULL)
		{

			direction = currentUnit->getPositionComponent()->getPosition() - pOwner->getPositionComponent()->getPosition();
			distance = direction.getLength();

			if (distance < mTHRESHOLD)
			{
				averageRotation += currentUnit->getFacing();
				++neighborCount;
			}

		}
	}


	if (neighborCount > 0)
	{
		averageRotation /= neighborCount;
		mapToRange(averageRotation);
		mTargetFacing = averageRotation;
		physicsData.rotAcc = AlignSteering::getSteering()->getData().rotAcc;
	}
	else
	{
		physicsData.rotAcc = 0;
		physicsData.rotVel = 0;
	}

	this->mData = physicsData;
	return this;
}
