#include <cassert>

#include "Steering.h"
#include "Game.h"
#include "SeekSteering.h"
#include "CohesionSteering.h"
#include "UnitManager.h"
#include "Unit.h"

CohesionSteering::CohesionSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering(), mSeekSteering(ownerID, targetLoc, targetID, shouldFlee)
{
	mType = COHESION;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering* CohesionSteering::getSteering()
{
	int i;
	float distance, strength;
	Vector2D direction, centerMassLoc;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();

	for (i = 0; i < gpGame->getUnitManager()->size(); i++)
	{
		mTargetLoc += gpGame->getUnitManager()->getUnit(i)->getPositionComponent()->getPosition();
	}

	centerMassLoc = mTargetLoc * (1 / (i + 1));
	direction = centerMassLoc - pOwner->getPositionComponent()->getPosition();
	distance = direction.getLength();

	//TODO: add seek
	if (distance > THRESHOLD) //if target is within cohesion radius, pull towards center of mass
	{
		physicsData = mSeekSteering.getSteering()->getData();
	}

	this->mData = physicsData;
	return this;
}
