#ifndef COIN_MAN_H
#define COIN_MAH_H

#include <Trackable.h>
#include <vector>

class Unit;
class Sprite;
class GrpahicsBuffer;
class GameApp;

class CoinManager : public Trackable
{
	private:
		GameApp * gameHandle;

		Unit** coinCollection;
		int* timeToSpawnList;
		//std::vector<int> emptyCoinIndexList;

		//Sprite mCoinSprite;
		int numberOfPowerUps = 4;
		int powerUpRespawnTime = 10, coinRespawnTime = 10;
		int maximumCoinsPossible, currentCoinCount;
		int secondsUntilRespawn;
		const int FPS = 30;
		const int COIN_SPRITE_SIZE = 16;

	public:
		CoinManager();
		~CoinManager();
		void cleanup();
		
		void trackCoin(Unit* coin);
		void initCoinCollection();

		void process();
		
		void setMaxCoinCount(int max) { maximumCoinsPossible = max; };
		void setPowerupAmount(int amount) { numberOfPowerUps = amount; };
		void setSecondsUntilCoinRespawn(int seconds) { coinRespawnTime = seconds; };
		void setSecondsUntilPowerupRespawn(int seconds) { powerUpRespawnTime = seconds; };
};

#endif // !COIN_MAN_H
