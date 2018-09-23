#ifndef ARRIVE_FACE_H
#define ARRIVE_FACE_H

#include <Trackable.h>
#include "Steering.h"

class ArriveFaceSteering : public ArriveSteering
{
	public:
		ArriveFaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);

	protected:
		FaceSteering mFaceSteering;
		Steering* mArriveSteeringData;
		Steering* mFaceSteeringData;

		virtual Steering* getSteering(); //overrides parent function
};

#endif //!ARRIVE_FACE_H