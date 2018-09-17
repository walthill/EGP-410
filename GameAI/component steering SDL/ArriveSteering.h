#include <Trackable.h>
#include "Steering.h"

class ArriveSteering : public Steering
{
public:
	ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);

protected:
	float mTargetRadius, mSlowRadius;
	const float mTIME_TO_TARGET = 0.1f;
	
	virtual Steering* getSteering(); //overrides parent function
};