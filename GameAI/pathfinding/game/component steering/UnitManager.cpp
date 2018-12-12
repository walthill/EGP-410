#include <map>
#include <vector>

#include "UnitManager.h"
#include "Unit.h"
#include "Game.h"
#include "ComponentManager.h"
#include "GraphicsSystem.h"
#include "../UnitStateMachine.h"
#include "../game/GameApp.h"
#include "Grid.h"

UnitID UnitManager::msNextUnitID = PLAYER_UNIT_ID + 1;

using namespace std;

UnitManager::UnitManager(Uint32 maxSize)
	:mPool(maxSize, sizeof(Unit))
{
}

UnitManager::~UnitManager()
{
	vector<Unit*> allUnits = getAllUnits();
	for (int i = 0; i < allUnits.size(); ++i)
	{
		if (allUnits[i]->getUnitID() == 0)
		{
			allUnits[i]->cleanup();
		}
		else if(allUnits[i]->hasState)
		{
			allUnits[i]->cleanup();
		}
		
	}
}

Unit* UnitManager::createUnit(unitType unitType, const Sprite& sprite, bool shouldWrap, const PositionData& posData /*= ZERO_POSITION_DATA*/, const PhysicsData& physicsData /*= ZERO_PHYSICS_DATA*/, const UnitID& id)
{
	Unit* pUnit = NULL;

	Byte* ptr = mPool.allocateObject();
	if (ptr != NULL)
	{
		//create unit
		pUnit = new (ptr)Unit(sprite);//placement new

		UnitID theID = id;
		if (theID == INVALID_UNIT_ID)
		{
			theID = msNextUnitID;
			msNextUnitID++;
		}

		//place in map
		mUnitMap[theID] = pUnit;

		//assign id and increment nextID counter
		pUnit->mID = theID;

		//create some components
		ComponentManager* pComponentManager = gpGame->getComponentManager();
		ComponentID id = pComponentManager->allocatePositionComponent(posData,shouldWrap);
		pUnit->mPositionComponentID = id;
		pUnit->mpPositionComponent = pComponentManager->getPositionComponent(id);
		pUnit->mPhysicsComponentID = pComponentManager->allocatePhysicsComponent(pUnit->mPositionComponentID, physicsData);
		pUnit->mSteeringComponentID = pComponentManager->allocateSteeringComponent(pUnit->mPhysicsComponentID);

		//set max's
		pUnit->mMaxSpeed = MAX_SPEED;
		pUnit->mMaxAcc = MAX_ACC;
		pUnit->mMaxRotAcc = MAX_ROT_ACC;
		pUnit->mMaxRotVel = MAX_ROT_VEL;
		
		if(unitType == PLAYER_UNIT)
		{
			pUnit->mUnitStateMachine = new UnitStateMachine(0, pUnit->mID);
			pUnit->setStateMachine(false);
		}
		if(unitType == ENEMY_UNIT)
		{
			pUnit->mUnitStateMachine = new UnitStateMachine(1, pUnit->mID);
			pUnit->setStateMachine(true);
		}
		if (unitType == COIN_UNIT)
		{
			pUnit->mUnitStateMachine = NULL;
			pUnit->setStateMachine(false);
		}
	}

	return pUnit;
}


Unit* UnitManager::createPlayerUnit(const Sprite& sprite, bool shouldWrap /*= true*/, const PositionData& posData /*= ZERO_POSITION_DATA*/, const PhysicsData& physicsData /*= ZERO_PHYSICS_DATA*/)
{
	return createUnit(PLAYER_UNIT, sprite, false, posData, physicsData, PLAYER_UNIT_ID);
}


//the one we want to call at this point
Unit* UnitManager::createRandomUnit(unitType unitType, const Sprite& sprite)
{
	int posX = rand() % gpGame->getGraphicsSystem()->getWidth();
	int posY = rand() % gpGame->getGraphicsSystem()->getHeight();

	GameApp* gpGameApp = dynamic_cast<GameApp*>(gpGame);
	int index = gpGameApp->getGrid()->getSquareIndexFromPixelXY(posX, posY);
	while (gpGameApp->getGrid()->getValueAtIndex(index) == BLOCKING_VALUE)
	{
		posX = rand() % gpGame->getGraphicsSystem()->getWidth();
		posY = rand() % gpGame->getGraphicsSystem()->getHeight();
		index = gpGameApp->getGrid()->getSquareIndexFromPixelXY(posX, posY);
	}
	
	Unit* pUnit = createUnit(unitType, sprite, true, PositionData(gpGameApp->getGrid()->getULCornerOfSquare(index), 0)); //Spawning a unit of type unitType

	if (pUnit != NULL)
		pUnit->setSteering(Steering::PATH_STEER, Vector2D(gpGame->getGraphicsSystem()->getWidth() / 2, gpGame->getGraphicsSystem()->getHeight() / 2));



	mIsNewUnit = true;
	mCallCount = 0; //track unit creation for flocking

	return pUnit;
}

Unit* UnitManager::createRandomUnit(unitType unitType, const Sprite& sprite, const UnitID& targetId)
{
	int posX = rand() % gpGame->getGraphicsSystem()->getWidth();
	int posY = rand() % gpGame->getGraphicsSystem()->getHeight();

	Unit* pUnit = createUnit(unitType, sprite, true, PositionData(Vector2D(posX, posY), 0));//Spawning an Enemy
	//pUnit->setShowTarget(true);
	if (pUnit != NULL)
		pUnit->setSteering(Steering::FLOCK, Vector2D(gpGame->getGraphicsSystem()->getWidth()/2, gpGame->getGraphicsSystem()->getHeight()/2));
	
	return pUnit;
}

vector<Unit*> UnitManager::getAllUnits()
{
	vector<Unit*> returnVector;
	mCallCount++;

	for (auto it = mUnitMap.begin(); it != mUnitMap.end(); ++it)
	{
		returnVector.push_back(it->second);
	}

	if (mCallCount > returnVector.size()) //no more new units being added
		mIsNewUnit = false;

	return returnVector;
}

bool UnitManager::hasNewUnit()
{
	return mIsNewUnit;
}

Unit* UnitManager::getUnit(const UnitID& id) const
{
	auto it = mUnitMap.find(id);
	if (it != mUnitMap.end())//found?
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}

void UnitManager::deleteUnit(const UnitID& id)
{
	auto it = mUnitMap.find(id);
	if (it != mUnitMap.end())//found?
	{
		Unit* pUnit = it->second;//hold for later

		//remove from map
		mUnitMap.erase(it);

		//remove components
		ComponentManager* pComponentManager = gpGame->getComponentManager();
		pComponentManager->deallocatePhysicsComponent(pUnit->mPhysicsComponentID);
		pComponentManager->deallocatePositionComponent(pUnit->mPositionComponentID);
		pComponentManager->deallocateSteeringComponent(pUnit->mSteeringComponentID);

		//call destructor
		pUnit->~Unit();

		//free the object in the pool
		mPool.freeObject((Byte*)pUnit);
	}
}

void UnitManager::deleteRandomUnit()
{
	if (mUnitMap.size() >= 1)
	{
		Uint32 cnt = 0;
		Uint32 target = rand() % mUnitMap.size();
		if (target == 0 && mUnitMap.size() == 1) //handle deleting last unit w/o player
		{
			target = 1;
			cnt = 1;
		}
		else if (target == 0)//don't allow the 0th element to be deleted as it is the player unit
		{
			target = 1;
		}

		for (auto it = mUnitMap.begin(); it != mUnitMap.end(); ++it, cnt++)
		{
			if (cnt == target)
			{
				deleteUnit(it->first);
				break;
			}
		}

		msNextUnitID--;
	}
}

void UnitManager::drawAll() const
{
	for (auto it = mUnitMap.begin(); it != mUnitMap.end(); ++it)
	{
		it->second->draw();
	}
}

void UnitManager::updateAll(float elapsedTime)
{
	for (auto it = mUnitMap.begin(); it != mUnitMap.end(); ++it)
	{
		it->second->update();
	}
}

int UnitManager::size()
{
	return mUnitMap.size();
}