#include <Trackable.h>
#include "Steering.h"

#define PI 3.14159265358979323846f

class AlignSteering : public Steering
{
public:
	AlignSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
	float mapToRange(float rotationInRadians);

protected:
	const float mTARGET_RADIUS = 0.01f;
	const float mSLOW_RADIUS = 0.5; //this should be bigger than target radius
	const float mTIME_TO_TARGET = 0.1f;
	float mTWO_PI = 2.0f*PI;

	virtual Steering* getSteering(); //overrides parent function
};