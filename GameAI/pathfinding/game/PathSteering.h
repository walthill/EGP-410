#ifndef PATH_STEER_H
#define PATH_STEER_H

#include "component steering\Steering.h"

class PathSteering : public Steering
{
	protected:

	public:
		PathSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
		virtual Steering* getSteering();
};

#endif // !PATH_STEER_H
