#ifndef GROUP_ALIGN_H
#define GROUP_ALIGN_H

#include <Trackable.h>
#include "Steering.h"
#include "FaceSteering.h"

class UnitManager;
class Unit;

class GroupAlignSteering: public FaceSteering
{
	public:
		GroupAlignSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
		virtual Steering* getSteering(); //overrides parent functions
	protected:
		const float mTHRESHOLD = 100.0f;
		
		UnitManager* unitManangerHandle;
		Unit* currentUnit;
		Unit* pOwner;
		int unitMapSize;
};

#endif // !GROUP_ALIGN_H


