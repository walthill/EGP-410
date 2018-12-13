#pragma once

#include <Trackable.h>
#include <DeanLibDefines.h>
#include <limits>
#include <Vector2D.h>
#include <Defines.h>

#include "Component.h"
#include "PositionComponent.h"
#include "Sprite.h"
#include "Steering.h"
#include "../game/Path.h"
#include "../Collider.h"
//#include "CircularQueue.h"
//#include "Transaction.h"
//#include "TransactionProcessor.h"

class PhysicsComponent;
class SteeringComponent;
class Sprite;
class UnitManager;
class UnitStateMachine;
class Collider;

const Uint32 DEFAULT_QUEUE_CAPACITY = 8;


//class Unit : public TransactionProcessor
class Unit : public Trackable
{
public:
	void draw() const;
	float getFacing() const;
	void update();
	void cleanup();

	PositionComponent* getPositionComponent() const;
	PhysicsComponent* getPhysicsComponent() const;
	SteeringComponent* getSteeringComponent() const;
	float getMaxAcc() const { return mMaxAcc; };
	float getMaxSpeed() const { return mMaxSpeed; };
	float getMaxRotAcc() const { return mMaxRotAcc; };
	float getMaxRotVel() const { return mMaxRotVel; };
	bool hasBeenDestroyed() const { return mDestroyed; };
	void setShowTarget(bool val) { mShowTarget = val; };
	void destroy() { mDestroyed = true; };
	void respawn() { mDestroyed = false; };
	UnitID getUnitID() { return mID; };
	void randomizePosition();
	void setStateMachine(bool state) { hasState = state; };
	
	void generatePath(Vector2D posToReach);
	void setPath(Path path);
	Path* getPath() { return &pathData.mPath; };
	std::vector<Vector2D> getPathInScreenSpace();
	int getNumPathNodes() { return pathData.numNodes; };
	bool stateMachineActive() { return hasState; };
	int getDestinationNode();
	bool canDelete = false;
	
	UnitStateMachine* mUnitStateMachine;

	bool checkCollision(Collider *colliderToCheck);
	Collider* getCollider();

	void setSteering(Steering::SteeringType type, Vector2D targetLoc = ZERO_VECTOR2D, UnitID targetUnitID = INVALID_UNIT_ID);

private:
	bool hasState;
	UnitID mID;
	ComponentID mPhysicsComponentID;
	ComponentID mPositionComponentID;
	ComponentID mSteeringComponentID;
	PositionComponent* mpPositionComponent = NULL;
	Sprite mSprite;
	float mMaxAcc;
	float mMaxSpeed;
	float mMaxRotAcc;
	float mMaxRotVel;
	bool mShowTarget;

	bool mDestroyed = false;

	struct CollisionData
	{
		Collider collider;
		//collder vars
		bool mHasCollided = false;
		int mLeftA, mLeftB, mRightA, mRightB;
		int mTopA, mTopB, mBottomA, mBottomB;
	}mCollisionData;

	struct PathData
	{
		Path mPath;
		std::vector<Vector2D> mPathPositions;
		int numNodes;
		int toNodeId;
	}pathData;

	Unit(const Sprite& sprite);
	virtual ~Unit();

	Unit(Unit&);//invalidate copy constructor
	void operator=(Unit&);//invalidate assignment operator

	friend class UnitManager;
};
