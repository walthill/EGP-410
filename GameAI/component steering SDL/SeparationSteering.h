#ifndef SEPARATE_H
#define SEPARATE_H

#include <Trackable.h>
#include "Steering.h"

class SeparationSteering : public Steering
{
	public:
		SeparationSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);

	protected:
		virtual Steering* getSteering(); //overrides parent function
		const float THRESHOLD = 50.0f; //minimum distance at which separation occurs
		const float DECAY = 35.0f; //how fast seperation strength decays over distance
};

#endif // !SEPARATE_H
