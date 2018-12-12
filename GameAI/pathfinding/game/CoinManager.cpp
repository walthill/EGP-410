#include "CoinManager.h"
#include "component steering/UnitManager.h"
#include "SpriteManager.h"
#include <time.h>
#include "GameApp.h"

CoinManager::CoinManager()
{
	maxNumCoins = 0;
	currentCoinCount = 0;
	emptyCoinIndexList.insert(emptyCoinIndexList.begin(), -1);
	
	srand(unsigned(time(NULL)));
}

CoinManager::~CoinManager()
{
	delete [] timeToSpawnList; //TODO: cleanup coin manager
}

void CoinManager::initCoinCollection()
{
	coinCollection = new Unit*[maxNumCoins];
	timeToSpawnList = new int[maxNumCoins];

	for (size_t i = 0; i < maxNumCoins; i++)
	{
		timeToSpawnList[i] = 0;
	}
}

void CoinManager::process()
{
	GameApp* gameHandle = dynamic_cast<GameApp*>(gpGame);

	//loop thru array up to current coin count, if any space is null, it's been deleted - start time to spawn a new one

	for (int i = 0; i < maxNumCoins; i++)
	{
		if (coinCollection[i] != nullptr)
		{
			if (coinCollection[i]->hasBeenDestroyed())
			{
				//add index to empty list
				if (std::find(emptyCoinIndexList.begin(), emptyCoinIndexList.end(), i) == emptyCoinIndexList.end())
				{
					emptyCoinIndexList.insert(emptyCoinIndexList.begin(), i);
					
					if (firstUpdate)
					{
						auto it = std::find(emptyCoinIndexList.begin(), emptyCoinIndexList.end(), -1);
						if (it != emptyCoinIndexList.end())
							emptyCoinIndexList.erase(it);

						firstUpdate = false;
					}
				}

				timeToSpawnList[i]++;

				if (timeToSpawnList[i] > secondsUntilRespawn*FPS)
				{
		
					//on respawn create new unit at a previous locataion
					//TODO: spawn at random, empty location

				//	if (emptyCoinIndexList.size() > 1)
					{
						cout << i << ": RESPAWN" << endl;

						Sprite* coinSprite = gameHandle->getSpriteManager()->getSprite(COIN_SPRITE_ID);
						Unit* pUnit = gameHandle->getUnitManager()->createUnit(COIN_UNIT, *coinSprite);

						int randVal = rand() % emptyCoinIndexList.size();
						int randomEmptyIndex = emptyCoinIndexList[randVal];

						float newX = coinCollection[randomEmptyIndex]->getPositionComponent()->getPosition().getX();
						float newY = coinCollection[randomEmptyIndex]->getPositionComponent()->getPosition().getY();

						Vector2D coinSpawnLoc(newX, newY);

						pUnit->getPositionComponent()->setPosition(coinSpawnLoc);

						pUnit->getCollider()->initCollider(pUnit->getPositionComponent()->getPosition().getX(),
							pUnit->getPositionComponent()->getPosition().getY(),
							COIN_SPRITE_SIZE, COIN_SPRITE_SIZE, COIN, pUnit);

						/*	while (coinCollection[randomEmptyIndex]->checkCollision(gameHandle->getUnitManager()->getPlayerUnit()->getCollider()))
							{
								cout << "Attempting to spawn on player" << endl;
								randVal = rand() % emptyCoinIndexList.size();
								randomEmptyIndex = emptyCoinIndexList[randVal];

								newX = coinCollection[randomEmptyIndex]->getPositionComponent()->getPosition().getX();
								newY = coinCollection[randomEmptyIndex]->getPositionComponent()->getPosition().getY();

								coinSpawnLoc.setX(newX);
								coinSpawnLoc.setY(newY);
								pUnit->getPositionComponent()->setPosition(coinSpawnLoc);

								pUnit->getCollider()->initCollider(pUnit->getPositionComponent()->getPosition().getX(),
									pUnit->getPositionComponent()->getPosition().getY(),
									COIN_SPRITE_SIZE, COIN_SPRITE_SIZE, COIN, pUnit);

							}*/

		/*					pUnit->getPositionComponent()->setPosition(coinSpawnLoc);

							pUnit->getCollider()->initCollider(pUnit->getPositionComponent()->getPosition().getX(),
								pUnit->getPositionComponent()->getPosition().getY(),
								COIN_SPRITE_SIZE, COIN_SPRITE_SIZE, COIN, pUnit);
		*/
							coinCollection[i] = pUnit;

							//for (int i = 0; i < maxNumCoins; i++)
								timeToSpawnList[i] = 0;

							auto it = std::find(emptyCoinIndexList.begin(), emptyCoinIndexList.end(), i);
							if ( it != emptyCoinIndexList.end())
							{
								emptyCoinIndexList.erase(it);
							}
					  }
				}
			}
		}
	}
}



void CoinManager::trackCoin(Unit* coin)
{ 
	coinCollection[currentCoinCount] = coin; 
	currentCoinCount++;  
}