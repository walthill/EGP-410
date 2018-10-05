#ifndef COHESION_H
#define COHESION_H

#include <Trackable.h>
#include "Steering.h"
#include "ArriveSteering.h"

class CohesionSteering : public Steering
{
	public:
		CohesionSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);

	protected:
		ArriveSteering mAriveSteering;
		virtual Steering* getSteering(); //overrides parent functions
		const float mTHRESHOLD = 100.0f;
		
		UnitManager* unitManangerHandle;
		Unit* currentUnit;
		Unit* pOwner;
		int unitMapSize;
};

#endif // !COHESION_H
