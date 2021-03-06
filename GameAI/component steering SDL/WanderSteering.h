#ifndef WANDER_H
#define WANDER_H

#include <Trackable.h>
#include "Steering.h"
#include "FaceSteering.h"

class WanderSteering : public Steering
{
	public:
		WanderSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
		virtual Steering* getSteering(); //overrides parent function
		virtual Steering* getSteering(std::vector<Unit*> unitList);
		Vector2D makeVector(float radiansToConvert);
	protected:
		FaceSteering mFaceSteering;
		float mWanderFacing;
		float mTargetFacing;

		//values to modify wander target 
		const float mWANDER_OFFSET = 100; //offset from owner
		const float mWANDER_RADIUS = 80;
		const float mWANDER_RATE = 2 * PI; //sets amount of circle used to find next target

};

#endif // !WANDER_H
