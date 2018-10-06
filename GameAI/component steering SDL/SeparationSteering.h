#ifndef SEPARATE_H
#define SEPARATE_H

#include <Trackable.h>
#include "Steering.h"

class SeparationSteering : public Steering
{
	public:
		SeparationSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
		void setRadius(float value) { mThreshold = value; };

	protected:
		virtual Steering* getSteering(); //overrides parent function
		virtual Steering* getSteering(std::vector<Unit*> unitList); //overrides parent function

		float mThreshold;// = 75.0f; //minimum distance at which separation occurs
		const float mDECAY = 100000.0f; //how fast seperation strength decays over distance
		
		UnitManager* unitManangerHandle;
		Unit* currentUnit;
		Unit* pOwner;
		int unitMapSize; 
};

#endif // !SEPARATE_H
