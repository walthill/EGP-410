#ifndef ARRIVE_H
#define ARRIVE_H

#include <Trackable.h>
#include "Steering.h"

class ArriveSteering : public Steering
{
	public:
		ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
		virtual Steering* getSteering(); //overrides parent function

		int getTargetRadius() { return mTARGET_RADIUS;}

	protected:

		//values to modify arrival smoothness
		const float mTARGET_RADIUS = 10;//0.1f;
		const float mSLOW_RADIUS = 100;//170; //this should be bigger than target radius
		const float mTIME_TO_TARGET = 0.5f;//0.1f;

};

#endif //!ARRIVE_H
