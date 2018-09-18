#include <Trackable.h>
#include "Steering.h"
#include <cmath>

class AlignSteering : public Steering
{
public:
	AlignSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);

protected:
	const float mTARGET_RADIUS = 0.5f;
	const float mSLOW_RADIUS = 170; //this should be bigger than target radius
	const float mTIME_TO_TARGET = 0.1f;
	float mTWO_PI = 2*3.141592f;

	virtual Steering* getSteering(); //overrides parent function
};