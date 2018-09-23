#ifndef ALIGN_H
#define ALIGN_H

#include <Trackable.h>
#include "Steering.h"

class AlignSteering : public Steering
{
	public:
		AlignSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
		float mapToRange(float rotationInRadians);
		virtual Steering* getSteering(); //overrides parent function
	protected:
		float mTargetFacing; //set in FaceSteering

		//values to modify smoothness of alignment
		const float mTARGET_RADIUS = 0.1f;
		const float mSLOW_RADIUS = 0.5f; //this should be bigger than target radius
		const float mTIME_TO_TARGET = 0.1f;
		
		const float mTWO_PI = 2.0f*PI;
};

#endif // !ALIGN_H
