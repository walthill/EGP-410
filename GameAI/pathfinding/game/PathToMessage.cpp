#include "PathToMessage.h"
#include "Game.h"
#include "GameApp.h"
#include "GridPathfinder.h"
#include "Grid.h"
#include "GridGraph.h"
#include "../game/component steering/Unit.h"
#include "AStarPathfinder.h"
#include "DijkstraPathfinder.h"
#include "DepthFirstPathfinder.h"


PathToMessage::PathToMessage(Unit* owner, const Vector2D& from, const Vector2D& to )
:GameMessage(PATH_TO_MESSAGE)
,mOwner(owner)
,mFrom(from)
,mTo(to)
{
}

PathToMessage::~PathToMessage()
{
}

void PathToMessage::process()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	if( pGame != NULL ) 
	{
		GridPathfinder* pPathfinder = NULL;
		//make this game's pathPool
		if (pGame->pathfinderIndex == 0)
		{
			pPathfinder = pGame->getPathPool()->getDepthPath(pGame->getPathPool()->queryPool(mOwner, mTo));
		}
		if (pGame->pathfinderIndex == 1)
		{
			pPathfinder = pGame->getPathPool()->getDijkstraPath(pGame->getPathPool()->queryPool(mOwner, mTo));
		}
		if (pGame->pathfinderIndex == 2)
		{
			pPathfinder = pGame->getPathPool()->getAStarPath(pGame->getPathPool()->queryPool(mOwner, mTo));
		}

		GridGraph* pGridGraph = pGame->getGridGraph();
		Grid* pGrid = pGame->getGrid();
		int fromIndex = pGrid->getSquareIndexFromPixelXY( (int)mFrom.getX(), (int)mFrom.getY() );
		int toIndex = pGrid->getSquareIndexFromPixelXY( (int)mTo.getX(), (int)mTo.getY() );
		Node* pFromNode = pGridGraph->getNode( fromIndex );
		Node* pToNode = pGridGraph->getNode( toIndex );
		
		//pOwner is in queue
		if (pPathfinder != NULL) 
		{
			//can't destroy this pointer
			Path* p = pPathfinder->findPath( pFromNode, pToNode );
			mOwner->setPath(*p);
			//cout << "unit pathing" << endl;
		}
		
		
	
		
	}
}
