#include "CoinManager.h"
#include "component steering/UnitManager.h"
#include "SpriteManager.h"
#include "GameApp.h"
#include "Grid.h"

CoinManager::CoinManager()
{
	gameHandle = dynamic_cast<GameApp*>(gpGame);
	maximumCoinsPossible = 0;
	currentCoinCount = 0;
}

CoinManager::~CoinManager()
{
	timeToSpawnList = NULL;
	coinCollection = NULL;
}

void CoinManager::cleanup()
{
	//delete [] timeToSpawnList; //TODO: cleanup coin manager
	//if (timeToSpawnList != NULL)
	{
		delete[] timeToSpawnList;
		timeToSpawnList = NULL;
	}
}


void CoinManager::initCoinCollection()
{
	coinCollection = new Unit*[maximumCoinsPossible];
	timeToSpawnList = new int[maximumCoinsPossible];

	for (int i = 0; i < maximumCoinsPossible; i++)
	{
		coinCollection[i] = NULL;
		timeToSpawnList[i] = 0;
	}
}

void CoinManager::process()
{
	//loop thru array up to current coin count, check if coin was collected - start time to spawn a new one

	for (int i = 0; i < currentCoinCount; i++)
	{
		if (coinCollection[i]->hasBeenDestroyed())
		{
			//respawn timer is run when coin has been destroyed
			timeToSpawnList[i]++;
			
			Sprite* spriteToSpawn;
			ColliderType colliderTag;
			if (i < currentCoinCount - numberOfPickups)
			{
				colliderTag = COIN;
				spriteToSpawn = gameHandle->getSpriteManager()->getSprite(COIN_SPRITE_ID);
				secondsUntilRespawn = coinRespawnTime;
			}
			else if(i >= currentCoinCount-numberOfPickups && i < currentCoinCount- numberOfHealth)
			{
				colliderTag = HEALTH_POWER;
				spriteToSpawn = gameHandle->getSpriteManager()->getSprite(HEALTH_POWER_SPRITE_ID);
				secondsUntilRespawn = powerUpRespawnTime;
			}
			else
			{
				colliderTag = POWERUP;
				spriteToSpawn = gameHandle->getSpriteManager()->getSprite(POWER_SPRITE_ID);
				secondsUntilRespawn = powerUpRespawnTime;
			}


			if (timeToSpawnList[i] > secondsUntilRespawn*FPS)
			{
				//randomize new coin position
				coinCollection[i]->randomizePosition();

				float x, y;
				x = coinCollection[i]->getPositionComponent()->getPosition().getX();
				y = coinCollection[i]->getPositionComponent()->getPosition().getY();
				
				int squareIndex = gameHandle->getGrid()->getSquareIndexFromPixelXY((int)x, (int)y);

				//check that new coin position is not a wall or occupied by another coin
				while(gameHandle->getGrid()->getValueAtIndex(squareIndex) == BLOCKING_VALUE || 
  					  gameHandle->getGrid()->getValueAtIndex(squareIndex) == COIN_VALUE)
				{


					coinCollection[i]->randomizePosition();

					x = coinCollection[i]->getPositionComponent()->getPosition().getX();
					y = coinCollection[i]->getPositionComponent()->getPosition().getY();

					squareIndex = gameHandle->getGrid()->getSquareIndexFromPixelXY((int)x, (int)y);
				}

				//Spawn new coin
				//Sprite* coinSprite = gameHandle->getSpriteManager()->getSprite(COIN_SPRITE_ID);
				Unit* pUnit = gameHandle->getUnitManager()->createUnit(COIN_UNIT, *spriteToSpawn);
				Vector2D coinSpawnLoc = gameHandle->getGrid()->getULCornerOfSquare(squareIndex);

				pUnit->getPositionComponent()->setPosition(coinSpawnLoc);

				pUnit->getCollider()->initCollider((int)pUnit->getPositionComponent()->getPosition().getX(),
												   (int)pUnit->getPositionComponent()->getPosition().getY(),
												   COIN_SPRITE_SIZE+2, COIN_SPRITE_SIZE+2, colliderTag, pUnit);

				//add new coin to collection
				coinCollection[i] = pUnit;
				
				//reset all respawn timers
				for (int j = 0; j < currentCoinCount; j++)
				{
					timeToSpawnList[j] = 0;
				}
				
				cout << "Respawning" << endl;
			}
		}
	}
}



void CoinManager::trackCoin(Unit* coin)
{ 
	coinCollection[currentCoinCount] = coin; 
	currentCoinCount++;  
}