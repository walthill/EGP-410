#include <Trackable.h>
#include "Steering.h"

class WanderSteering : public Steering
{
public:
	WanderSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
	Vector2D makeVector(float radiansToConvert);
protected:
	FaceSteering mFaceSteering;
	float mWanderFacing;
	float mTargetFacing;

	const float mWANDER_OFFSET = 100;
	const float mWANDER_RADIUS = 80;
	const float mWANDER_RATE = 2*PI;

	virtual Steering* getSteering(); //overrides parent function
};