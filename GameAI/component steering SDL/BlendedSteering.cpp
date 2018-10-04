#include "BlendedSteering.h"
#include "Steering.h"

#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


BlendedSteering::BlendedSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering()
{
	mType = FLOCK;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering* BlendedSteering::getSteering()
{
	Vector2D direction;

	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();

	for (unsigned int i =0; i < behaviorList.size(); i++)
	{
		BehaviorAndWeight tmp = behaviorList[i];
		weightedAcc += tmp.behavior->getSteering()->getData().acc * tmp.weight;
		weightedRotAcc += tmp.behavior->getSteering()->getData().rotAcc * tmp.weight;
	}

	if (weightedAcc.getLength() > physicsData.maxAccMagnitude)
	{
		weightedAcc = physicsData.maxAccMagnitude;
	}

	if (weightedRotAcc> physicsData.maxRotAcc)
	{
		weightedAcc = physicsData.maxAccMagnitude;
	}

	physicsData.acc = weightedAcc;
	physicsData.rotAcc = weightedRotAcc;

	this->mData = physicsData;
	return this;
}

void BlendedSteering::setBehaviorList(Steering *behavior, float weight)
{
	BehaviorAndWeight itemToAdd;
	itemToAdd.behavior = behavior;
	itemToAdd.weight = weight;
	behaviorList.push_back(itemToAdd);
}