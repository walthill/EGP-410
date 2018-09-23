#ifndef FACE_H
#define FACE_H

#include <Trackable.h>
#include "Steering.h"

class FaceSteering : public AlignSteering
{
	public:
		FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
		virtual Steering* getSteering(); //overrides parent function - public for use as member variable

};

#endif // !FACE_H
