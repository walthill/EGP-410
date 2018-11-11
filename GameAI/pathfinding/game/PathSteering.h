#ifndef PATH_STEER_H
#define PATH_STEER_H

#include "component steering/Steering.h"
#include "component steering/SeekSteering.h"

class Path;
class GameApp;

class PathSteering : public Steering
{
	private:
		GameApp* gameAppHandle;
		int nextLocationIndex = 1;
		bool hasArrived;
	protected:
		SeekSteering mSeekSteering;

	public:
		PathSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
		virtual Steering* getSteering();
};

#endif // !PATH_STEER_H
