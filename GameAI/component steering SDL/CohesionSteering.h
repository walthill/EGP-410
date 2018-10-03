#ifndef COHESION_H
#define COHESION_H

#include <Trackable.h>
#include "Steering.h"
#include "SeekSteering.h"

class CohesionSteering : public Steering
{
	public:
		CohesionSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);

	protected:
		SeekSteering mSeekSteering;
		virtual Steering* getSteering(); //overrides parent functions
		const float THRESHOLD = 100.0f; 
		//const float DECAY = 1.0f; 

};

#endif // !COHESION_H
