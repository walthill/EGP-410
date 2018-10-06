#ifndef BLEND_STEER_H
#define BLEND_STEER_H

#include <Trackable.h>
#include <vector>
#include "Steering.h"
#include "GroupAlign.h"

enum BehaviorType { WANDER, GROUP_ALIGN, COHESION, SEPARATION };

class BlendedSteering : public Steering
{
	public:	
		BlendedSteering::BlendedSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/);
		void setBehaviorList(Steering *behavior, float weight);
		void setWeight(BehaviorType behvaiorType, float weight);
		virtual Steering* getSteering(); //overrides parent functions


	protected:
		struct BehaviorAndWeight
		{
			Steering* behavior;
			float weight;
		};
		
		std::vector<Unit*> unitList; //container
		std::vector<BehaviorAndWeight> behaviorList;
};

#endif // !BLEND_STEER_H
