#include "Unit.h"
#include <assert.h>
#include "GraphicsSystem.h"
#include "Component.h"
#include "PositionComponent.h"
#include "PhysicsComponent.h"
#include "SteeringComponent.h"
#include "ComponentManager.h"
#include "SpriteManager.h"
#include "../game/PathToMessage.h"
#include "../game/GameMessage.h"
#include "../game/GameMessageManager.h"
#include "../game/Node.h"
#include "../common/Grid.h"
#include "../game/GameApp.h"
#include "../game/IdleState.h"
#include "../game/WanderState.h"
#include "../game/ChaseState.h"
#include"../game/FleeState.h"
#include "../game/UnitStateMachine.h"


Unit::Unit(const Sprite& sprite) 
	:mSprite(sprite)
	,mPositionComponentID(INVALID_COMPONENT_ID)
	,mPhysicsComponentID(INVALID_COMPONENT_ID)
	,mSteeringComponentID(INVALID_COMPONENT_ID)
	,mShowTarget(false)
{
	pathData = {};
}


Unit::~Unit()
{
	mDestroyed = true;
}

void Unit::cleanup() 
{
	delete mUnitStateMachine->pIdleState;
	delete mUnitStateMachine->pWanderState;
	delete mUnitStateMachine->pChaseState;
	delete mUnitStateMachine->pFleeState;

	delete mUnitStateMachine->pToIdleTrans;
	delete mUnitStateMachine->pToWanderTrans;
	delete mUnitStateMachine->pToChaseTrans;
	delete mUnitStateMachine->pToFleeTrans;

	delete mUnitStateMachine;
}

void Unit::update(float elapsedTime)
{
	//keep collider on top of the unit
	mCollisionData.collider.setX(getPositionComponent()->getPosition().getX());
	mCollisionData.collider.setY(getPositionComponent()->getPosition().getY());


	mUnitStateMachine->update();
}

void Unit::draw() const
{
	if (!mDestroyed)
	{
		PositionComponent* pPosition = getPositionComponent();
		assert(pPosition != NULL);
		const Vector2D& pos = pPosition->getPosition();
		gpGame->getGraphicsSystem()->draw(mSprite, pos.getX(), pos.getY(), pPosition->getFacing());

		if (mShowTarget)
		{
			SteeringComponent* pSteering = getSteeringComponent();
			assert(pSteering != NULL);
			const Vector2D& targetLoc = pSteering->getTargetLoc();
			if (&targetLoc != &ZERO_VECTOR2D)
			{
				Sprite* pTargetSprite = gpGame->getSpriteManager()->getSprite(TARGET_SPRITE_ID);
				assert(pTargetSprite != NULL);
				gpGame->getGraphicsSystem()->draw(*pTargetSprite, targetLoc.getX(), targetLoc.getY());
			}
		}
	}
}

float Unit::getFacing() const
{
	PositionComponent* pPosition = getPositionComponent();
	assert(pPosition != NULL);
	return pPosition->getFacing();
}

PositionComponent* Unit::getPositionComponent() const
{
	return mpPositionComponent;
}

PhysicsComponent* Unit::getPhysicsComponent() const
{
	PhysicsComponent* pComponent = gpGame->getComponentManager()->getPhysicsComponent(mPhysicsComponentID);
	return pComponent;
}

SteeringComponent* Unit::getSteeringComponent() const
{
	SteeringComponent* pComponent = gpGame->getComponentManager()->getSteeringComponent(mSteeringComponentID);
	return pComponent;
}

void Unit::setSteering(Steering::SteeringType type, Vector2D targetLoc /*= ZERO_VECTOR2D*/, UnitID targetUnitID /*= INVALID_UNIT_ID*/)
{
	SteeringComponent* pSteeringComponent = getSteeringComponent();
	if (pSteeringComponent != NULL)
	{
		pSteeringComponent->setData(SteeringData(type, targetLoc, mID, targetUnitID));
	}
}

void Unit::randomizePosition()
{
	int x = rand() % gpGame->getGraphicsSystem()->getWidth();
	int y = rand() % gpGame->getGraphicsSystem()->getHeight();
	Vector2D pos(x, y);

	mpPositionComponent->setPosition(pos);
}

void Unit::generatePath(Vector2D posToReach)
{
	GameApp* gpGameApp = dynamic_cast<GameApp*>(gpGame);
	if (mpPositionComponent->getPosition().getX() != posToReach.getX() || mpPositionComponent->getPosition().getY() != posToReach.getY())
	{
		GameMessage* pMessage = new PathToMessage(this, mpPositionComponent->getPosition(), posToReach);
		gpGameApp->mpMessageManager->addMessage(pMessage, 0);
		//lastPos = pos;
	}
}

void Unit::setPath(Path path)
{
	GameApp* gpGameApp = dynamic_cast<GameApp*>(gpGame);

	pathData.mPath = path;

	{
		pathData.numNodes = pathData.mPath.getNumNodes();

		pathData.mPathPositions.resize(pathData.numNodes);

		for (int i = pathData.numNodes; i > 0; i--)
		{
			pathData.mPathPositions[i-1] = gpGameApp->getGrid()->getULCornerOfSquare(pathData.mPath.peekNode(i-1)->getId());
		
			float x = pathData.mPathPositions[i - 1].getX() + 16;
			float y = pathData.mPathPositions[i - 1].getY() + 16;

			pathData.mPathPositions[i - 1].setX(x);
			pathData.mPathPositions[i - 1].setY(y);
		}
	}

	if (pathData.mPathPositions.size() > 0)
	{
		Vector2D toVector = pathData.mPathPositions[pathData.mPathPositions.size() - 1];
		pathData.toNodeId = gpGameApp->getGrid()->getSquareIndexFromPixelXY(toVector.getX(), toVector.getY());
	}
}

std::vector<Vector2D> Unit::getPathInScreenSpace()
{
	return pathData.mPathPositions;
}

int Unit::getDestinationNode()
{
	return pathData.toNodeId;
}



bool Unit::checkCollision( Collider *colliderToCheck)
{
	//assert(mHasCollider); //you're checking for collisions w/o a collider

	//if (b->getUnit()->isVisible())
	{
		//calculate sides of a
		mCollisionData.mLeftA = mCollisionData.collider.getX();
		mCollisionData.mRightA = mCollisionData.mLeftA + mCollisionData.collider.getW();
		mCollisionData.mTopA = mCollisionData.collider.getY();
		mCollisionData.mBottomA = mCollisionData.mTopA + mCollisionData.collider.getH();

		//calculate sides of b
		mCollisionData.mLeftB = colliderToCheck->getX();
		mCollisionData.mRightB = mCollisionData.mLeftB + colliderToCheck->getW();
		mCollisionData.mTopB = colliderToCheck->getY();
		mCollisionData.mBottomB = mCollisionData.mTopB + colliderToCheck->getH();

		//collision detection
		if (mCollisionData.mBottomA <= mCollisionData.mTopB)
		{
			return false; //NO COLLUSION...i mean collision
		}
		if (mCollisionData.mTopA >= mCollisionData.mBottomB)
		{
			return false;
		}
		if (mCollisionData.mRightA <= mCollisionData.mLeftB)
		{
			return false;
		}
		if (mCollisionData.mLeftA >= mCollisionData.mRightB)
		{
			return false;
		}

		return true;

	}
	//	return false;

}

Collider* Unit::getCollider()
{ 
	return &mCollisionData.collider;
}