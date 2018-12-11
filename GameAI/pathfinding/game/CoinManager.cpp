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
	if (timeToSpawnList != NULL)
	{
	//	delete[] timeToSpawnList;

	//	timeToSpawnList = NULL;
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

			if (timeToSpawnList[i] > secondsUntilRespawn*FPS)
			{
				//randomize new coin position
				coinCollection[i]->randomizePosition();

				int x, y;
				x = coinCollection[i]->getPositionComponent()->getPosition().getX();
				y = coinCollection[i]->getPositionComponent()->getPosition().getY();
				
				int squareIndex = gameHandle->getGrid()->getSquareIndexFromPixelXY(x, y);

				//check that new coin position is not a wall or occupied by another coin
				while(gameHandle->getGrid()->getValueAtIndex(squareIndex) == BLOCKING_VALUE || 
  					  gameHandle->getGrid()->getValueAtIndex(squareIndex) == COIN_VALUE)
				{
					cout << "COINWALL" << endl;

					coinCollection[i]->randomizePosition();

					x = coinCollection[i]->getPositionComponent()->getPosition().getX();
					y = coinCollection[i]->getPositionComponent()->getPosition().getY();

					squareIndex = gameHandle->getGrid()->getSquareIndexFromPixelXY(x, y);
				}

				//Spawn new coin
				Sprite* coinSprite = gameHandle->getSpriteManager()->getSprite(COIN_SPRITE_ID);
				Unit* pUnit = gameHandle->getUnitManager()->createUnit(*coinSprite);
				Vector2D coinSpawnLoc = gameHandle->getGrid()->getULCornerOfSquare(squareIndex);

				pUnit->getPositionComponent()->setPosition(coinSpawnLoc);

				pUnit->getCollider()->initCollider(pUnit->getPositionComponent()->getPosition().getX(),
												   pUnit->getPositionComponent()->getPosition().getY(),
												   COIN_SPRITE_SIZE, COIN_SPRITE_SIZE, COIN, pUnit);

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