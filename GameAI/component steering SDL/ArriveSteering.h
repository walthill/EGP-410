#include <Trackable.h>
#include "Steering.h"

class ArriveSteering : public Steering
{
public:
	ArriveSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);

protected:
	const float mTARGET_RADIUS = 0.5f;
	const float mSLOW_RADIUS = 170; //this should be bigger than target radius
	const float mTIME_TO_TARGET = 0.1f;
	
	virtual Steering* getSteering(); //overrides parent function
};