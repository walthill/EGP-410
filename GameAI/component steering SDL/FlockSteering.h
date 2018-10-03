#ifndef FLOCK_H
#define FLOCK_H

#include <Trackable.h>
#include "Steering.h"
#include "BlendedSteering.h"

class FlockSteering : public WanderSteering
{

	public:
		FlockSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);

	protected:
		virtual Steering* getSteering(); //overrides parent functions

		BlendedSteering mBlendSteering;
		GroupAlignSteering mGroupAlignSteering;
		CohesionSteering mCohesionSteering;
		SeparationSteering mSeparationSteering;

};

#endif // !FLOCK_H

