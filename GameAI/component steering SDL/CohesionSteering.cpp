#include <cassert>

#include "Steering.h"
#include "Game.h"
#include "CohesionSteering.h"
#include "UnitManager.h"
#include "Unit.h"

//TODO: pass in a list of targets?
CohesionSteering::CohesionSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering()
{
	mType = COHESION;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering* CohesionSteering::getSteering()
{
	Vector2D direction;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();

	return this;
}
