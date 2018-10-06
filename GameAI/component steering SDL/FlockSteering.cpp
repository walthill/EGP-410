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

	mCohesionSteering.setRadius(gpGame->getFlockData().cohesionRadius);
	mSeparationSteering.setRadius(gpGame->getFlockData().separationRadius);
	mGroupAlignSteering.setRadius(gpGame->getFlockData().groupAlignRadius);
	mBlendSteering.setBehaviorList(mWanderSteering, gpGame->getFlockData().wanderWeight); //wander is pointer
	mBlendSteering.setBehaviorList(&mGroupAlignSteering, gpGame->getFlockData().groupAlignWeight);
	mBlendSteering.setBehaviorList(&mCohesionSteering, gpGame->getFlockData().cohesionWeight);
	mBlendSteering.setBehaviorList(&mSeparationSteering, gpGame->getFlockData().seaparationWeight);
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
	
	if (gpGame->checkWeightChange())
	{
		mBlendSteering.setWeight(BehaviorType::WANDER, gpGame->getFlockData().wanderWeight);
		mBlendSteering.setWeight(BehaviorType::GROUP_ALIGN, gpGame->getFlockData().groupAlignWeight);
		mBlendSteering.setWeight(BehaviorType::COHESION, gpGame->getFlockData().cohesionWeight);
		mBlendSteering.setWeight(BehaviorType::SEPARATION, gpGame->getFlockData().seaparationWeight);

		gpGame->setWeightChange(false);
	}

	if (gpGame->checkRadiusChange())
	{
		mCohesionSteering.setRadius(gpGame->getFlockData().cohesionRadius);
		mSeparationSteering.setRadius(gpGame->getFlockData().separationRadius);
		mGroupAlignSteering.setRadius(gpGame->getFlockData().groupAlignRadius);

		gpGame->setRadiusChange(false);
	}

	physicsData = mBlendSteering.getSteering()->getData();
	
	this->mData = physicsData;
	return this;
}
