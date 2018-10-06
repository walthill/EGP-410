#include <cassert>

#include "Steering.h"
#include "Game.h"
#include "SeparationSteering.h"
#include "UnitManager.h"
#include "Unit.h"

SeparationSteering::SeparationSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering()
{
	mType = SEPARATION;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	unitManangerHandle = gpGame->getUnitManager();
}

Steering* SeparationSteering::getSteering() { return this; }

Steering* SeparationSteering::getSteering(std::vector<Unit*> unitList)
{
	int neighborCount = 0;
	float distance, strength;
	Vector2D direction = Vector2D();
	pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData physicsData = pOwner->getPhysicsComponent()->getData();
	unitMapSize = unitList.size();

	for (int i = 0; i < unitMapSize; i++)
	{	
		currentUnit = unitList[i];
		
		if (pOwner != currentUnit && currentUnit != NULL)
		{
			
			direction = currentUnit->getPositionComponent()->getPosition() - pOwner->getPositionComponent()->getPosition();
			distance = direction.getLength();

			if (distance < mThreshold)
			{
				strength = min(mDECAY / (distance*distance), pOwner->getMaxAcc()); //inverse square
				
				direction *= -1;
				direction.normalize();
				physicsData.acc += (direction * strength);

				++neighborCount;
			}
		}
	}

	if (neighborCount == 0)
	{
		physicsData.acc = 0;
		physicsData.vel = 0;
	}

	this->mData = physicsData;
	return this;
}
