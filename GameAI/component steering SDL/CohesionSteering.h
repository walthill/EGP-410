#ifndef COHESION_H
#define COHESION_H

#include <Trackable.h>
#include "Steering.h"

class CohesionSteering : public Steering
{
	public:
		CohesionSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);

	protected:
		virtual Steering* getSteering(); //overrides parent functions
};

#endif // !COHESION_H
