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
#include "CoinManager.h"
#include "EnemyPool.h"

#include "simpleini-4.17\SimpleIni.h"
#include "DepthFirstPathfinder.h"

#include "InputManager.h"

#include <SDL.h>
#include <fstream>
#include <vector>
#include <time.h>

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

	loadGameData();

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
	
	mpPathfinder = new AStarPathfinder(mpGridGraph);
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

	GraphicsBuffer* pHealthPowerBuffer = mpGraphicsBufferManager->getBuffer(mHealthIconBufferID);
	Sprite* pHealthPowerSprite = NULL;
	if (pHealthPowerBuffer != NULL)
	{
		pHealthPowerSprite = mpSpriteManager->createAndManageSprite(HEALTH_POWER_SPRITE_ID, pHealthPowerBuffer, 0, 0, (float)pHealthPowerBuffer->getWidth(), (float)pHealthPowerBuffer->getHeight());
	}

	GraphicsBuffer* pPowerBuffer = mpGraphicsBufferManager->getBuffer(mPowerIconBufferID);
	Sprite* pPowerSprite = NULL;
	if (pPowerBuffer != NULL)
	{
		pPowerSprite = mpSpriteManager->createAndManageSprite(POWER_SPRITE_ID, pPowerBuffer, 0, 0, (float)pPowerBuffer->getWidth(), (float)pPowerBuffer->getHeight());
	}


	//Initializing player 

	Unit* pUnit = mpUnitManager->createPlayerUnit(*pArrowSprite);
	pUnit->setShowTarget(false);
	pUnit->setSteering(Steering::PATH_STEER, ZERO_VECTOR2D);

	srand(unsigned(time(NULL)));

	//Add enemies
	totalEnemies = 10;										//Make this data driven
	mpEnemyPool = new EnemyPool();

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

			pUnit->getPositionComponent()->setPosition(mpGrid->getULCornerOfSquare(squareIndex));

			adjacencies = mpGrid->getAdjacentIndices(squareIndex);
			adjIndex = 0;
		}
	}

	mPlayer = new Player();
	mPlayer->hookPlayerUnit(pUnit);
	mPlayer->getPlayerUnit()->getCollider()->initCollider(pUnit->getPositionComponent()->getPosition().getX(),
														  pUnit->getPositionComponent()->getPosition().getY(),
												    	  16, 16, PLAYER, pUnit);



	//int maxNumberOfCoins = 0;// = 10;


	//setup maximum possible coin value
	for (int i = 0; i < mpGrid->getGridHeight()*mpGrid->getGridWidth(); i++)
	{
		if (mpGrid->getValueAtIndex(i) != BLOCKING_VALUE)
		{
			maxNumberOfCoins++;
		}
	}

	mCoinManager = new CoinManager();
	mCoinManager->setMaxCoinCount(maxNumberOfCoins);
	mCoinManager->initCoinCollection();

	mCoinManager->setSecondsUntilCoinRespawn(mCoinSpawnTime);
	mCoinManager->setSecondsUntilPowerupRespawn(mPowerSpawnTime);
	
	int maxPowerUps = mNumberOfPowerups + mNumberOfHealthPickups;
	mCoinManager->setPowerupAmount(maxPowerUps);

	if (mCoinSpacingStartIndex >= mCoinSpacing-1)
		mCoinSpacingStartIndex = 0;

	int intervalCounter = mCoinSpacingStartIndex;
	
	//place coin at every clear grid location to start game
	for (int i = 0; i < mpGrid->getGridHeight()*mpGrid->getGridWidth(); i++)
	{
		if (mpGrid->getValueAtIndex(i) != BLOCKING_VALUE)
		{
			intervalCounter++;

			if (intervalCounter >= mCoinSpacing)
			{
				Vector2D coinPos = mpGrid->getULCornerOfSquare(i);
				coinPos.setX(coinPos.getX() + 16);
				coinPos.setY(coinPos.getY() + 16);

				Unit* pUnit = mpUnitManager->createUnit(*pCoinSprite);
				pUnit->getPositionComponent()->setPosition(coinPos);

				pUnit->getCollider()->initCollider(pUnit->getPositionComponent()->getPosition().getX(),
					pUnit->getPositionComponent()->getPosition().getY(),
					16 + 2, 16 + 2, COIN, pUnit);

				mCoinManager->trackCoin(pUnit);
				mpGrid->setValueAtIndex(i, COIN_VALUE);
				intervalCounter = mCoinSpacingStartIndex;
			}
		}
	}
	
	//power ups
	int powerUpCounter = 0;

	for (int i = 0; i < maxPowerUps; i++)
	{
		powerUpCounter++;

		ColliderType tag;
		Sprite* spriteToSpawn;
		if (powerUpCounter <= mNumberOfHealthPickups)
		{
			spriteToSpawn = pHealthPowerSprite;
			tag = HEALTH_POWER;
		}
		else if (powerUpCounter > mNumberOfHealthPickups && powerUpCounter <= maxPowerUps)
		{
			spriteToSpawn = pPowerSprite;
			tag = POWERUP;
		}

		Unit* pUnit = mpUnitManager->createUnit(*spriteToSpawn);
		pUnit->randomizePosition();
		float x = pUnit->getPositionComponent()->getPosition().getX();
		float y = pUnit->getPositionComponent()->getPosition().getY();

		int squareIndex = mpGrid->getSquareIndexFromPixelXY(x, y);

		while (mpGrid->getValueAtIndex(squareIndex) == BLOCKING_VALUE 
			   || mpGrid->getValueAtIndex(squareIndex) == COIN_VALUE)
		{
			pUnit->randomizePosition();
			x = pUnit->getPositionComponent()->getPosition().getX();
			y = pUnit->getPositionComponent()->getPosition().getY();

			squareIndex = mpGrid->getSquareIndexFromPixelXY(x, y);
		}

		Vector2D pos = mpGrid->getULCornerOfSquare(squareIndex);

		pUnit->getPositionComponent()->setPosition(pos);
		
		pUnit->getCollider()->initCollider(pUnit->getPositionComponent()->getPosition().getX(),
											pUnit->getPositionComponent()->getPosition().getY(),
											16+2, 16+2, tag, pUnit);

		mCoinManager->trackCoin(pUnit);
		mpGrid->setValueAtIndex(squareIndex, COIN_VALUE);
	}

	//debug display
	pContent = new PathfindingDebugContent( mpPathfinder );
	pContent->setPathfindingType(A_STAR_PATH);
	mpDebugDisplay = new DebugDisplay( Vector2D(0,12), pContent );


	//THIS IS WHERE WE DECIDE HOW MANY PATHS ARE IN THE POOL!
	mpPathPool = new PathPool(15);

	mpMasterTimer->start();
	return true;
}


void GameApp::loadGameData()
{
	cout << "Loading game data from " + mINI_FILE << endl;
	//"section", "key",	default, "filename"
	CSimpleIniA ini;
	ini.SetUnicode();
	ini.LoadFile(mINI_FILE.c_str());

	const char * iniCoinSpacing = ini.GetValue("PICKUPVALUES", "coinspacing", "default");
	const char * iniCoinTimer = ini.GetValue("PICKUPVALUES", "cointime", "default");
	const char * iniPowerTimer = ini.GetValue("PICKUPVALUES", "powertime", "default");
	const char * iniHealthPickups = ini.GetValue("PICKUPVALUES", "healthamount", "default");
	const char * iniPowerupPickups = ini.GetValue("PICKUPVALUES", "powerupamount", "default");
	const char * iniCoinSpaceStart = ini.GetValue("PICKUPVALUES", "coinspacestart", "default");

	mCoinSpacingStartIndex = atoi(iniCoinSpaceStart);
	mNumberOfHealthPickups = atoi(iniHealthPickups);
	mNumberOfPowerups = atoi(iniPowerupPickups);
	mCoinSpacing = atoi(iniCoinSpacing);
	mPowerSpawnTime = atoi(iniPowerTimer);
	mCoinSpawnTime= atoi(iniCoinTimer);
}

void GameApp::cleanup()
{
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

	delete mpUnitManager;
	mpUnitManager = NULL;

	mCoinManager->cleanup();
	delete mCoinManager;
	mCoinManager = NULL;

	delete mPlayer;
	mPlayer = NULL;
}

void GameApp::beginLoop()
{
	//should be the first thing done
	Game::beginLoop();
}

void GameApp::processLoop()
{
	//mPlayer->process(mpUnitManager->getAllUnits());                                          !
	//mCoinManager->process();
	
	//get back buffer
	GraphicsBuffer* pBackBuffer = mpGraphicsSystem->getBackBuffer();
	//copy to back buffer
	mpGridVisualizer->draw( *pBackBuffer );

#ifdef VISUALIZE_PATH
	//show pathfinder visualizer
	mpPathfinder->drawVisualization(mpGrid, pBackBuffer);
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




