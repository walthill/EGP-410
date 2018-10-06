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
	Vector2D direction, weightedAcc = (0.0f, 0.0f);
	float weightedRotAcc = 0;
	BehaviorAndWeight tmpBehaviorData;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();
	Steering* behaviorSteering;

	if (gpGame->getUnitManager()->hasNewUnit())
		unitList = gpGame->getUnitManager()->getAllUnits();

	physicsData.acc = 0;
	physicsData.rotAcc = 0;

	for (unsigned int i =0; i < behaviorList.size(); i++)
	{
		tmpBehaviorData = behaviorList[i];
		behaviorSteering = tmpBehaviorData.behavior->getSteering(unitList);
		physicsData.acc += (behaviorSteering->getData().acc * tmpBehaviorData.weight);
		physicsData.rotAcc += (behaviorSteering->getData().rotAcc * tmpBehaviorData.weight);
	}

	physicsData.acc.normalize();
	physicsData.acc *= pOwner->getMaxAcc();

	if (physicsData.rotAcc > pOwner->getMaxRotAcc())
	{
		physicsData.rotAcc = pOwner->getMaxRotAcc();
	}

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


void BlendedSteering::setWeight(BehaviorType behaviorType, float weight)
{
	behaviorList[behaviorType].weight = weight;
}