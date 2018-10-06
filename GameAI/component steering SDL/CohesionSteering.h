#ifndef COHESION_H
#define COHESION_H

#include <Trackable.h>
#include "Steering.h"
#include "ArriveSteering.h"

class CohesionSteering : public Steering
{
	public:
		CohesionSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
		void setRadius(float value) { mThreshold = value; };

	protected:
		virtual Steering* getSteering(); //overrides parent functions
		virtual Steering* getSteering(std::vector<Unit*> unitList); //overrides parent function

		ArriveSteering mAriveSteering;

		float mThreshold;// = 100.0f;
		
		UnitManager* unitManangerHandle;
		Unit* currentUnit;
		Unit* pOwner;
		int unitMapSize;
};

#endif // !COHESION_H
