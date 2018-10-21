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
#include "DepthFirstPathfinder.h"
#include "DijkstraPathfinder.h"
#include "AStarPathfinder.h"
#include "Pathfinder.h"
#include "GridPathfinder.h"
#include "GridVisualizer.h"
#include "DebugDisplay.h"
#include "PathfindingDebugContent.h"
#include "../game/EventListener.h"
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
	installListeners();
	//mpMessageManager = new GameMessageManager();

	//create and load the Grid, GridBuffer, and GridRenderer
	mpGrid = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);
	mpGridVisualizer = new GridVisualizer( mpGrid );
	std::ifstream theStream( gFileName );
	mpGrid->load( theStream );

	//create the GridGraph for pathfinding
	mpGridGraph = new GridGraph(mpGrid);
	//init the nodes and connections
	mpGridGraph->init();

	mpPathfinder = new DepthFirstPathfinder(mpGridGraph);

	//load buffers
	mpGraphicsBufferManager->loadBuffer(mBackgroundBufferID, "wallpaper.bmp");

	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( mBackgroundBufferID );
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, (float)pBackGroundBuffer->getWidth(), (float)pBackGroundBuffer->getHeight() );
	}

	//debug display
	pContent = new PathfindingDebugContent( mpPathfinder );
	pContent->setPathfindingType(DEPTH_FIRST_PATH);
	mpDebugDisplay = new DebugDisplay( Vector2D(0,12), pContent );

	mpMasterTimer->start();
	return true;
}


void GameApp::installListeners()
{
	EventSystem::getInstance()->addListener(QUIT, this);
	EventSystem::getInstance()->addListener(ASTAR, this);
	EventSystem::getInstance()->addListener(DIJKSTRA, this);
	EventSystem::getInstance()->addListener(DEPTH_FIRST, this);
	EventSystem::getInstance()->addListener(SET_PATH, this);
}


void GameApp::cleanup()
{
//	delete mpMessageManager;
//	mpMessageManager = NULL;

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
	//get back buffer
	GraphicsBuffer* pBackBuffer = mpGraphicsSystem->getBackBuffer();
	//copy to back buffer
	mpGridVisualizer->draw( *pBackBuffer );
#ifdef VISUALIZE_PATH
	//show pathfinder visualizer
	mpPathfinder->drawVisualization(mpGrid, pBackBuffer);
#endif
	mpDebugDisplay->draw( pBackBuffer );
	
	mpInputSystem->update(LOOP_TARGET_TIME);

	//should be last thing in processLoop
	Game::processLoop();
}

bool GameApp::endLoop()
{
	return Game::endLoop();
}



void GameApp::handleEvent(const Event& theEvent)
{
	mEventType = theEvent.getType();

	switch (mEventType)
	{
	case SET_PATH:
	{
		const MouseEvent& mouseEvent = static_cast<const MouseEvent&>(theEvent);
		float x = (float)mouseEvent.getX();
		float y = (float)mouseEvent.getY();

		static Vector2D lastPos(0.0f, 0.0f); //pathfinding will always start from top left
		Vector2D pos(x, y);
		if (lastPos.getX() != pos.getX() || lastPos.getY() != pos.getY())
		{
			int fromIndex = mpGrid->getSquareIndexFromPixelXY((int)lastPos.getX(), (int)lastPos.getY());
			int toIndex = mpGrid->getSquareIndexFromPixelXY((int)pos.getX(), (int)pos.getY());
			Node* pFromNode = mpGridGraph->getNode(fromIndex);
			Node* pToNode = mpGridGraph->getNode(toIndex);
			mpPathfinder->findPath(pFromNode, pToNode);	

			lastPos = pos;
		}

		break;
	}
	case QUIT:
		mShouldExit = true;
		break;
	case DEPTH_FIRST:
		{
			if (mpPathfinder != NULL)
			{
				delete mpPathfinder;
				delete mpDebugDisplay;
			}

			mpPathfinder = new DepthFirstPathfinder(mpGridGraph);
			pContent = new PathfindingDebugContent(mpPathfinder);
			pContent->setPathfindingType(DEPTH_FIRST_PATH);
			mpDebugDisplay = new DebugDisplay(Vector2D(0, 12), pContent);
			cout << "DEPTH FIRST" << endl;
			break;
		}
		case DIJKSTRA:
		{
			if (mpPathfinder != NULL)
			{
				delete mpPathfinder;
				delete mpDebugDisplay;
			}

			mpPathfinder = new DijkstraPathfinder(mpGridGraph);
			pContent = new PathfindingDebugContent(mpPathfinder);
			pContent->setPathfindingType(DIJSKTRA_PATH);
			mpDebugDisplay = new DebugDisplay(Vector2D(0, 12), pContent);
			cout << "DIJKSTRA" << endl;
			break;
		}
		case ASTAR:
		{
			if (mpPathfinder != NULL)
			{
				delete mpPathfinder;
				delete mpDebugDisplay;
			}

			mpPathfinder = new AStarPathfinder(mpGridGraph);
			pContent = new PathfindingDebugContent(mpPathfinder);
			pContent->setPathfindingType(A_STAR_PATH);
			mpDebugDisplay = new DebugDisplay(Vector2D(0, 12), pContent);
			cout << "A STAR" << endl;
			break;
		}


	}
}