#include <Trackable.h>
#include "Steering.h"

class WanderSteering : public FaceSteering
{
public:
	WanderSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
	Vector2D makeVector(float radiansToConvert);
protected:
	float mWanderFacing;

	const float mWANDER_OFFSET = 5;
	const float mWANDER_RADIUS = 100;
	const float mWANDER_RATE = 2;

	virtual Steering* getSteering(); //overrides parent function
};