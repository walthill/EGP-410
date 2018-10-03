#ifndef GROUP_ALIGN_H
#define GROUP_ALIGN_H

#include <Trackable.h>
#include "Steering.h"
#include "AlignSteering.h"

class GroupAlignSteering: public AlignSteering
{
	public:
		GroupAlignSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
		virtual Steering* getSteering(); //overrides parent functions
	protected:
		
		//float closestNeighbor = INVALID_UNIT_ID;
		const float THRESHOLD = 50.0f;
};

#endif // !GROUP_ALIGN_H


