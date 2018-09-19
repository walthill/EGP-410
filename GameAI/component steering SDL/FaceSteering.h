#include <Trackable.h>
#include "Steering.h"

class FaceSteering : public AlignSteering
{
public:
	FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
	
protected:
	virtual Steering* getSteering(); //overrides parent function
};