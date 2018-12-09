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
}

void Unit::draw() const
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
		collisionData.mLeftA = collisionData.collider.getX();
		collisionData.mRightA = collisionData.mLeftA + collisionData.collider.getW();
		collisionData.mTopA = collisionData.collider.getY();
		collisionData.mBottomA = collisionData.mTopA + collisionData.collider.getH();

		//calculate sides of b
		collisionData.mLeftB = colliderToCheck->getX();
		collisionData.mRightB = collisionData.mLeftB + colliderToCheck->getW();
		collisionData.mTopB = colliderToCheck->getY();
		collisionData.mBottomB = collisionData.mTopB + colliderToCheck->getH();

		//collision detection
		if (collisionData.mBottomA <= collisionData.mTopB)
		{
			return false; //NO COLLUSION...i mean collision
		}
		if (collisionData.mTopA >= collisionData.mBottomB)
		{
			return false;
		}
		if (collisionData.mRightA <= collisionData.mLeftB)
		{
			return false;
		}
		if (collisionData.mLeftA >= collisionData.mRightB)
		{
			return false;
		}

		return true;

	}
	//	return false;

}

Collider* Unit::getCollider()
{ 
	return &collisionData.collider; 
}