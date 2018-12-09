#ifndef COIN_MAN_H
#define COIN_MAH_H

#include <Trackable.h>
#include <vector>

class Unit;
class Sprite;
class GrpahicsBuffer;

class CoinManager : public Trackable
{
	private:
		Unit** coinCollection;
		int* timeToSpawnList;
		std::vector<int> emptyCoinIndexList;

		//Sprite mCoinSprite;

		int maxNumCoins, currentCoinCount;
		int secondsUntilRespawn = 10;
		const int FPS = 30;
		const int COIN_SPRITE_SIZE = 16;

		bool firstUpdate = true;

	public:
		CoinManager();
	//	CoinManager(Sprite& coinSprite);
		~CoinManager();

		void trackCoin(Unit* coin);
		void initCoinCollection();

		void process();
		
		void setMaxCoinCount(int max) { maxNumCoins = max; };
};

#endif // !COIN_MAN_H
