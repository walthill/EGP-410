#include <cassert>

#include "Steering.h"
#include "Game.h"
#include "ArriveSteering.h"
#include "CohesionSteering.h"
#include "UnitManager.h"
#include "Unit.h"

CohesionSteering::CohesionSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering(), mAriveSteering(ownerID, targetLoc, targetID, shouldFlee)
{
	mType = COHESION;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	unitManangerHandle = gpGame->getUnitManager();
}

Steering* CohesionSteering::getSteering() { return this; }

Steering* CohesionSteering::getSteering(std::vector<Unit*> unitList)
{
	int i, neighborCount =0;
	float distance;
	Vector2D direction, centerMassLoc;
	pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();
	unitMapSize = unitList.size();

	for (int i = 0; i < unitMapSize; i++)
	{
		currentUnit = unitList[i];
		
		if (currentUnit != pOwner && currentUnit != NULL)
		{
			direction = currentUnit->getPositionComponent()->getPosition() - pOwner->getPositionComponent()->getPosition();
			distance = direction.getLength();

			if (distance < mThreshold) //if target is within cohesion radius, pull towards center of mass
			{
				centerMassLoc += currentUnit->getPositionComponent()->getPosition();
				++neighborCount;
			}
		}
	}


	if (neighborCount > 0)
	{
		centerMassLoc /= neighborCount;
		mAriveSteering.setTargetLoc(centerMassLoc);
		mAriveSteering.getSteering();
		physicsData.acc = mAriveSteering.getData().acc;
	}
	else
	{
		physicsData.acc = 0;
		physicsData.vel = 0;
	}	

	this->mData = physicsData;
	return this;
}
