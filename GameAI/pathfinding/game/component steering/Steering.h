#ifndef STEERING_H
#define STEERING_H

/*Steering - implementation of Steering class from "Artificial Intelligence for Games" - Millington and Funge
*/

#include <Vector2D.h>
#include <Trackable.h>
#include <vector>
#include <Defines.h>
#include "PhysicsComponent.h"

class Unit;

class Steering : public Trackable
{
public:
	enum SteeringType
	{
		INVALID_TYPE = -1,
		SEEK,
		FLEE,
		ARRIVE,
		ALIGN,
		FACE,
		WANDER,
		ARRIVE_FACE,
		WANDER_CHASE,
		SEPARATION,
		COHESION,
		GROUP_ALIGN,
		FLOCK,
		PATH_STEER
	};

	//constructors and destructors
	Steering(SteeringType type = INVALID_TYPE) :mType(type), mTargetLoc(ZERO_VECTOR2D), mTargetID(INVALID_UNIT_ID), mOwnerID(INVALID_UNIT_ID), mData(ZERO_PHYSICS_DATA) {};
	virtual ~Steering() {};

	//accessors
	void setTargetLoc(const Vector2D& loc) { mTargetLoc = loc; };
	const Vector2D& getTargetLoc() const { return mTargetLoc; };
	void setTargetID(const UnitID& id) { mTargetID = id; };
	const UnitID& getTargetID() const { return mTargetID; };
	void setOwnerID(const UnitID& id) { mOwnerID = id; };
	//void setData(const PhysicsData& data) { mData = data; };
	const PhysicsData& getData() const { return mData; };
	void update();
	virtual Steering* getSteering() { return this; };//overridden by sub-classes
	virtual Steering* getSteering(std::vector<Unit*> unitList) { return this; }; //overidden by flocking sub-classes
protected:
	SteeringType mType;
	Vector2D mTargetLoc;
	UnitID mTargetID;
	UnitID mOwnerID;
	PhysicsData mData;



};

#endif // !STEERING_H
