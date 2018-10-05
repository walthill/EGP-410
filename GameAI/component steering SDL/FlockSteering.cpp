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
	: mCohesionSteering(ownerID, targetLoc, targetID, shouldFlee), mBlendSteering(ownerID, targetLoc, targetID, shouldFlee),
	mSeparationSteering(ownerID, targetLoc, targetID, shouldFlee), mGroupAlignSteering(ownerID, targetLoc, targetID, shouldFlee)
{
	mWanderSteering = new WanderSteering(ownerID, targetLoc, targetID, shouldFlee);
	
	mType = FLOCK;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);

	mBlendSteering.setBehaviorList(mWanderSteering, 1.0f);
	mBlendSteering.setBehaviorList(&mGroupAlignSteering, 1.0f);
	mBlendSteering.setBehaviorList(&mCohesionSteering, 0.7f);
	mBlendSteering.setBehaviorList(&mSeparationSteering, 1.0f);
}

FlockSteering::~FlockSteering()
{
	delete mWanderSteering;
	mWanderSteering = NULL;
}

Steering* FlockSteering::getSteering()
{
	Vector2D direction;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();
	physicsData.acc = 0;
	physicsData.rotAcc = 0;

	physicsData = mBlendSteering.getSteering()->getData();
	
	this->mData = physicsData;
	return this;
}
