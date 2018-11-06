#include "Game.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include "GridGraph.h"
#include "KeyDownMessage.h"
#include "DepthFirstPathfinder.h"
#include "DijkstraPathfinder.h"
#include "AStarPathfinder.h"
#include "DebugDisplay.h"
#include "PathfindingDebugContent.h"
#include "Vector2D.h"
#include "component steering/UnitManager.h"
#include "SpriteManager.h"


KeyDownMessage::KeyDownMessage(const int& key)
	:GameMessage(BUTTON_DOWN)
	, mKey(key)
{
}

KeyDownMessage::~KeyDownMessage()
{
}

void KeyDownMessage::process()
{
	GameApp* gpGameApp = dynamic_cast<GameApp*>(gpGame);


	if (gpGameApp != NULL)
	{
		//exit game
		if (mKey == 0)
		{
			gpGame->markForExit();
		}
		//F Depth First Search
		if (mKey == 1)
		{
			if (gpGameApp->mpPathfinder != NULL)
			{
				delete gpGameApp->mpPathfinder;
				delete gpGameApp->mpDebugDisplay;
			}

			gpGameApp->mpPathfinder = new DepthFirstPathfinder(gpGameApp->mpGridGraph);
			gpGameApp->pContent = new PathfindingDebugContent(gpGameApp->mpPathfinder);
			gpGameApp->pContent->setPathfindingType(DEPTH_FIRST_PATH);
			gpGameApp->mpDebugDisplay = new DebugDisplay(Vector2D(0, 12), gpGameApp->pContent);
			cout << "DEPTH FIRST" << endl;
		}
		//D Dijkstra Pathfinding
		if (mKey == 2)
		{
			if (gpGameApp->mpPathfinder != NULL)
			{
				delete gpGameApp->mpPathfinder;
				delete gpGameApp->mpDebugDisplay;
			}

			gpGameApp->mpPathfinder = new DijkstraPathfinder(gpGameApp->mpGridGraph);
			gpGameApp->pContent = new PathfindingDebugContent(gpGameApp->mpPathfinder);
			gpGameApp->pContent->setPathfindingType(DIJSKTRA_PATH);
			gpGameApp->mpDebugDisplay = new DebugDisplay(Vector2D(0, 12), gpGameApp->pContent);
			cout << "DIJKSTRA" << endl;
		}
		//A A* pathfinding
		if (mKey == 3)
		{
			if (gpGameApp->mpPathfinder != NULL)
			{
				delete gpGameApp->mpPathfinder;
				delete gpGameApp->mpDebugDisplay;
			}

			gpGameApp->mpPathfinder = new AStarPathfinder(gpGameApp->mpGridGraph);
			gpGameApp->pContent = new PathfindingDebugContent(gpGameApp->mpPathfinder);
			gpGameApp->pContent->setPathfindingType(A_STAR_PATH);
			gpGameApp->mpDebugDisplay = new DebugDisplay(Vector2D(0, 12), gpGameApp->pContent);
			cout << "A STAR" << endl;
		}
		if (mKey == 4)
		{
			while(gpGameApp->getUnitManager()->size() > 0)
				gpGameApp->getUnitManager()->deleteRandomUnit();

			for (int i = 0; i < 10; i++)
			{
				cout << "NEW UNIT " << i << endl;
				Sprite* tmpSpr = gpGameApp->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID);
				gpGameApp->getUnitManager()->createRandomUnit(*tmpSpr);

				//TODO: make sure arrows don't spawn on walls
			}
		}
	}
}