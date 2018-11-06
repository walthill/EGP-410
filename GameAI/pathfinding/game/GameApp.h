#pragma once

/*Game - class to hold all game related info.

Dean Lawson
Champlain College
2011
*/

#include "Game.h"
#include "InputManager.h"

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

class GameApp: public Game
{
public:
	GameApp();
	~GameApp();

	virtual bool init();
	virtual void cleanup();

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

	GridPathfinder* mpPathfinder;
	GridGraph* mpGridGraph;
	GameMessageManager* mpMessageManager;
	PathfindingDebugContent *pContent;
	DebugDisplay* mpDebugDisplay;

private:
	Grid* mpGrid;
	GridVisualizer* mpGridVisualizer;
	InputManager* mpInput;

};

