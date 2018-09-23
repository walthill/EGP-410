#ifndef SEEK_H
#define SEEK_H

#include <Trackable.h>
#include "Steering.h"

class SeekSteering : public Steering
{
	public:
		SeekSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
		virtual Steering* getSteering(); //overrides parent function - public for use as member variable
};

#endif //!SEEK_H