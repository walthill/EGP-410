#include "Steering.h"
#include "Game.h"
#include "CohesionSteering.h"
#include "AlignSteering.h"
#include "SeparationSteering.h"
#include "GroupAlign.h"
#include "WanderSteering.h"
#include "FlockSteering.h"
#include "UnitManager.h"
#include "Unit.h"

FlockSteering::FlockSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: WanderSteering(ownerID, targetLoc, targetID, shouldFlee), mBlendSteering(ownerID, targetLoc, targetID, shouldFlee), mCohesionSteering(ownerID, targetLoc, targetID, shouldFlee),
	mSeparationSteering(ownerID, targetLoc, targetID, shouldFlee), mGroupAlignSteering(ownerID, targetLoc, targetID, shouldFlee)
{
	mType = FLOCK;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);

	mBlendSteering.setBehaviorList(mGroupAlignSteering, 0.1f);
	mBlendSteering.setBehaviorList(mCohesionSteering, 0.4f);
	mBlendSteering.setBehaviorList(mSeparationSteering, 0.5f);
}

Steering* FlockSteering::getSteering()
{
	Vector2D direction;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();

	physicsData = WanderSteering::getSteering()->getData();
	
	PhysicsData tmp = mBlendSteering.getSteering()->getData();
	physicsData.acc += tmp.acc;
	physicsData.rotAcc += tmp.rotAcc;

	this->mData = physicsData;
	return this;
}
