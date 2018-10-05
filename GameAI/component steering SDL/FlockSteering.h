#ifndef FLOCK_H
#define FLOCK_H

#include <Trackable.h>
#include "Steering.h"
#include "BlendedSteering.h"

class FlockSteering : public Steering
{

	public:
		FlockSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
		virtual ~FlockSteering();
	protected:
		virtual Steering* getSteering(); //overrides parent functions

		BlendedSteering mBlendSteering;
		GroupAlignSteering mGroupAlignSteering;
		CohesionSteering mCohesionSteering;
		SeparationSteering mSeparationSteering;
		WanderSteering* mWanderSteering;

};

#endif // !FLOCK_H

