#ifndef BLEND_STEER_H
#define BLEND_STEER_H

#include <Trackable.h>
#include <vector>
#include "Steering.h"
#include "GroupAlign.h"
class BlendedSteering : public Steering
{
	public:	
		BlendedSteering::BlendedSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/);
		void BlendedSteering::setBehaviorList(Steering *behavior, float weight);
		virtual Steering* getSteering(); //overrides parent functions


	protected:
		struct BehaviorAndWeight
		{
			Steering* behavior;
			float weight; //value less than one
		};

		std::vector<BehaviorAndWeight> behaviorList;
};

#endif // !BLEND_STEER_H
