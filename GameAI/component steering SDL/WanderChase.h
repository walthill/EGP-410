#ifndef WANDER_CHASE_H
#define WANDER_CHASE_H

#include <Trackable.h>
#include "Steering.h"

class WanderChaseSteering : public WanderSteering
{
	public:
		WanderChaseSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);

	protected:
		SeekSteering mSeekSteering;

		Steering *mSteeringData, *mFaceSteeringData;

		const float mSEEK_RADIUS = 300;

		virtual Steering* getSteering(); //overrides parent function
};

#endif // !WANDER_CHASE_H
