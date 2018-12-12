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
class PathfindingDebugContent;
class DebugDisplay;
class Player;
class CoinManager;

class GameApp: public Game
{
public:
	GameApp();
	~GameApp();

	virtual bool init();
	virtual void cleanup();

	void loadGameData();

	//game loop
	virtual void beginLoop();
	virtual void processLoop();
	virtual bool endLoop();

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
	PathfindingDebugContent *pContent;
	DebugDisplay* mpDebugDisplay;

	int pathfinderIndex;
	std::vector<Path*> gpPaths;

private:
	Grid* mpGrid;
	GridVisualizer* mpGridVisualizer;
	InputManager* mpInput;
	PathPool* mpPathPool;

	Player* mPlayer;
	CoinManager* mCoinManager;

	//data driven variables
	const string mINI_FILE = "data.ini";

	int mCoinSpawnTime, mPowerSpawnTime, mCoinSpacing, mCoinSpacingStartIndex;
	int mNumberOfHealthPickups, mNumberOfPowerups;
};

