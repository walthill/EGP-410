#pragma once

/*Game - class to hold all game related info.

Dean Lawson
Champlain College
2011
*/

#include "Game.h"
#include "InputManager.h"
#include "PathPool.h"
#include <vector>
#include "Path.h"

//forward declarations
class GraphicsBuffer;
class Sprite;
class KinematicUnit;
class GameMessageManager;
class Grid;
class GridVisualizer;
class GridGraph;
class GridPathfinder;
class ScoreboardContent;
class DebugDisplay;
class Player;
class CoinManager;
class EnemyPool;

class GameApp: public Game
{
public:
	GameApp();
	~GameApp();

	virtual bool init();
	virtual void cleanup();

	void initItemPickups();
	void loadGameData();

	//game loop
	virtual void beginLoop();
	virtual void processLoop();
	virtual bool endLoop();

	void lose();
	void tickSurvivalTimer();
	void addCoinScore();
	void addPowerupScore();


	//accessors
	inline GameMessageManager* getMessageManager() { return mpMessageManager; };
	inline GridVisualizer* getGridVisualizer() { return mpGridVisualizer; };
	inline GridPathfinder* getPathfinder() { return mpPathfinder; };
	inline Grid* getGrid() { return mpGrid; };
	inline GridGraph* getGridGraph() { return mpGridGraph; };
	inline PathPool* getPathPool() { return mpPathPool; };
	inline InputManager* getInputManager() { return mpInput; };

	GridPathfinder* mpPathfinder;
	GridGraph* mpGridGraph;
	GameMessageManager* mpMessageManager;
//	PathfindingDebugContent *pContent;
	ScoreboardContent *pContent;
	DebugDisplay* mpDebugDisplay;

	int pathfinderIndex;
	std::vector<Path*> gpPaths;
	int totalEnemies;
	EnemyPool* mpEnemyPool;

private:
	Grid* mpGrid;
	GridVisualizer* mpGridVisualizer;
	InputManager* mpInput;
	PathPool* mpPathPool;
	Timer* survivalTimer;
	Player* mPlayer;
	CoinManager* mCoinManager;

	bool lost = false;

	//data driven variables
	const string mINI_FILE = "data.ini";

	int mCoinSpawnTime, mPowerSpawnTime, mCoinSpacing, mCoinSpacingStartIndex;
	int mNumberOfHealthPickups, mNumberOfPowerups, mNumberOfEnemies, mCoinScoreValue, mPowerupScoreValue;
	int mPlayerHealth, mEnemyHealth;
	int mScore = 0, mTime = 0, timer = 0;
	string mFlavorText, mLostText;

	double millisec = 0;
	int sec = 0, min = 0;
};

