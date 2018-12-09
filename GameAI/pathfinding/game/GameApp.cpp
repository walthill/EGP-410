#include "Game.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include "PathToMessage.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include <Vector2D.h>
#include "Grid.h"
#include "GridGraph.h"
#include "Connection.h"
#include "Path.h"
#include "Pathfinder.h"
#include "GridPathfinder.h"
#include "GridVisualizer.h"
#include "DebugDisplay.h"
#include "PathfindingDebugContent.h"
#include "../game/AStarPathfinder.h"
#include "../game/component steering/UnitManager.h"
#include "Player.h"

#include "DepthFirstPathfinder.h"

#include "InputManager.h"

#include <SDL.h>
#include <fstream>
#include <vector>

const int GRID_SQUARE_SIZE = 32;
const std::string gFileName = "pathgrid.txt";

GameApp::GameApp()
:Game()
,mpGrid(NULL)
,mpGridGraph(NULL)
,mpPathfinder(NULL)
,mpDebugDisplay(NULL)
{
}

GameApp::~GameApp()
{
	cleanup();
}

bool GameApp::init()
{
	bool retVal = Game::init();

	if( retVal == false )
	{

		return false;
	}
	//installListeners();
	mpMessageManager = new GameMessageManager();

	mpInput = new InputManager();

	//create and load the Grid, GridBuffer, and GridRenderer
	mpGrid = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);
	mpGridVisualizer = new GridVisualizer( mpGrid );
	std::ifstream theStream( gFileName );
	mpGrid->load( theStream );

	//create the GridGraph for pathfinding
	mpGridGraph = new GridGraph(mpGrid);
	//init the nodes and connections
	mpGridGraph->init();
//	mpPathfinder = new DepthFirstPathfinder(mpGridGraph);
	mpPathfinder = new AStarPathfinder(mpGridGraph);
	//mpPathfinder = 
	pathfinderIndex = 2;

	//load buffers
	mpGraphicsBufferManager->loadBuffer(mBackgroundBufferID, "wallpaper.bmp");

	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( mBackgroundBufferID );
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, (float)pBackGroundBuffer->getWidth(), (float)pBackGroundBuffer->getHeight() );
	}

	GraphicsBuffer* pPlayerBuffer = mpGraphicsBufferManager->getBuffer(mPlayerIconBufferID);
	Sprite* pArrowSprite = NULL;
	if (pPlayerBuffer != NULL)
	{
		pArrowSprite = mpSpriteManager->createAndManageSprite(PLAYER_ICON_SPRITE_ID, pPlayerBuffer, 0, 0, (float)pPlayerBuffer->getWidth(), (float)pPlayerBuffer->getHeight());
	}
	GraphicsBuffer* pCoinBuffer = mpGraphicsBufferManager->getBuffer(mCoinIconBufferID);
	Sprite* pCoinSprite = NULL;
	if (pCoinBuffer != NULL)
	{
		pCoinSprite = mpSpriteManager->createAndManageSprite(COIN_SPRITE_ID, pCoinBuffer, 0, 0, (float)pCoinBuffer->getWidth(), (float)pCoinBuffer->getHeight());
	}

	//Initializing player 

	Unit* pUnit = mpUnitManager->createPlayerUnit(*pArrowSprite);
	pUnit->setShowTarget(false);
	pUnit->setSteering(Steering::PATH_STEER, ZERO_VECTOR2D);

	float x = pUnit->getPositionComponent()->getPosition().getX();
	float y = pUnit->getPositionComponent()->getPosition().getY();

	//check if unit is within or adjacent to a wall tile, randomize its position until it is not
	int squareIndex = mpGrid->getSquareIndexFromPixelXY(x, y);
	std::vector<int> adjacencies = mpGrid->getAdjacentIndices(squareIndex);

	for (unsigned int adjIndex = 0; adjIndex < adjacencies.size(); adjIndex++)
	{
		while (mpGrid->getValueAtIndex(adjacencies[adjIndex]) == BLOCKING_VALUE)
		{
			cout << "WALL" << endl;
			pUnit->randomizePosition();

			x = pUnit->getPositionComponent()->getPosition().getX();
			y = pUnit->getPositionComponent()->getPosition().getY();

			squareIndex = mpGrid->getSquareIndexFromPixelXY(x, y);

			adjacencies = mpGrid->getAdjacentIndices(squareIndex);
			adjIndex = 0;
		}
	}

	mPlayer = new Player();
	mPlayer->hookPlayerUnit(pUnit);
	mPlayer->getPlayerUnit()->getCollider()->initCollider(pUnit->getPositionComponent()->getPosition().getX(),
														  pUnit->getPositionComponent()->getPosition().getY(),
												    	  16, 16, PLAYER, pUnit);



	//int numCoins = 10;
	
	for (size_t i = 0; i < mpGrid->getGridHeight()*mpGrid->getGridWidth(); i++)
	{
		if (mpGrid->getValueAtIndex(i) != BLOCKING_VALUE)
		{
			Vector2D coinPos =  mpGrid->getULCornerOfSquare(i);
			coinPos.setX(coinPos.getX() + 16);
			coinPos.setY(coinPos.getY() + 16);
			Unit* pUnit = mpUnitManager->createUnit(*pCoinSprite);
			pUnit->getPositionComponent()->setPosition(coinPos);
			
			pUnit->getCollider()->initCollider(pUnit->getPositionComponent()->getPosition().getX(),
									    	   pUnit->getPositionComponent()->getPosition().getY(),
											   16, 16, COIN, pUnit);
			
			//mpGrid->setValueAtIndex(i, COIN_VALUE);
			//cout << i << ": " << mpGrid->getValueAtIndex(i);
		}
	}

	//spawn coins
/*	for (size_t i = 0; i < numCoins; i++)
	{
		Unit* pUnit = mpUnitManager->createRandomUnit(*pCoinSprite);
	//	UnitID currentUnitID = pUnit->getUnitID();

		float x = pUnit->getPositionComponent()->getPosition().getX();
		float y = pUnit->getPositionComponent()->getPosition().getY();

		//check if unit is within or adjacent to a wall tile, randomize its position until it is not
		int squareIndex = mpGrid->getSquareIndexFromPixelXY(x, y);
		std::vector<int> adjacencies = mpGrid->getAdjacentIndices(squareIndex);

		for (unsigned int adjIndex = 0; adjIndex < adjacencies.size(); adjIndex++)
		{
			while (mpGrid->getValueAtIndex(adjacencies[adjIndex]) == BLOCKING_VALUE)
			{
				cout << "COINWALL" << endl;
				pUnit->randomizePosition();
				x = pUnit->getPositionComponent()->getPosition().getX();
				y = pUnit->getPositionComponent()->getPosition().getY();

				squareIndex = mpGrid->getSquareIndexFromPixelXY(x, y);

				adjacencies = mpGrid->getAdjacentIndices(squareIndex);
				adjIndex = 0;
			}
		}

		/*if (mpGrid->getValueAtIndex(squareIndex) == COIN_VALUE)
		{
			cout << "delete coin" << endl;
			mpUnitManager->deleteUnit(currentUnitID);
		}
		else
		{
			mpGrid->setValueAtIndex(squareIndex, COIN_VALUE);
		}
	}*/

	//debug display
	pContent = new PathfindingDebugContent( mpPathfinder );
	pContent->setPathfindingType(A_STAR_PATH);
	mpDebugDisplay = new DebugDisplay( Vector2D(0,12), pContent );


	//THIS IS WHERE WE DECIDE HOW MANY PATHS ARE IN THE POOL!
	mpPathPool = new PathPool(5);


	mpMasterTimer->start();
	return true;
}


void GameApp::cleanup()
{
//	delete mPlayer;

	int size = gpPaths.size();
	for (int i = 0; i < size; i++)
	{
		delete gpPaths[0];
		gpPaths.erase(gpPaths.begin());
	}
	gpPaths.clear();

	delete mpPathPool;
	mpPathPool = NULL;
	
	delete mpMessageManager;
	mpMessageManager = NULL;

	delete mpGrid;
	mpGrid = NULL;

	delete mpGridVisualizer;
	mpGridVisualizer = NULL;

	delete mpGridGraph;
	mpGridGraph = NULL;

	delete mpPathfinder;
	mpPathfinder = NULL;

	delete mpDebugDisplay;
	mpDebugDisplay = NULL;

	
//	delete mpInputSystem;
}

void GameApp::beginLoop()
{
	//should be the first thing done
	Game::beginLoop();
}

void GameApp::processLoop()
{
	mPlayer->process(mpUnitManager->getAllUnits());
	
	//get back buffer
	GraphicsBuffer* pBackBuffer = mpGraphicsSystem->getBackBuffer();
	//copy to back buffer
	mpGridVisualizer->draw( *pBackBuffer );
#ifdef VISUALIZE_PATH
	//show pathfinder visualizer
	//mpPathfinder->drawVisualization(mpGrid, pBackBuffer);
#endif
	
	mpDebugDisplay->draw( pBackBuffer );
	
	mpMessageManager->processMessagesForThisframe();
	mpInput->process();

	mpPathPool->process();

	//should be last thing in processLoop
	Game::processLoop();
}

bool GameApp::endLoop()
{
	return Game::endLoop();
}




