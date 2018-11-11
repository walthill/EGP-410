#include "PathToMessage.h"
#include "Game.h"
#include "GameApp.h"
#include "GridPathfinder.h"
#include "Grid.h"
#include "GridGraph.h"
#include "../game/component steering/Unit.h"


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
		GridPathfinder* pPathfinder = pGame->getPathfinder();
		GridGraph* pGridGraph = pGame->getGridGraph();
		Grid* pGrid = pGame->getGrid();
		int fromIndex = pGrid->getSquareIndexFromPixelXY( (int)mFrom.getX(), (int)mFrom.getY() );
		int toIndex = pGrid->getSquareIndexFromPixelXY( (int)mTo.getX(), (int)mTo.getY() );
		Node* pFromNode = pGridGraph->getNode( fromIndex );
		Node* pToNode = pGridGraph->getNode( toIndex );
		
		//can't destroy this pointer
		Path* p = pPathfinder->findPath( pFromNode, pToNode );
		
		mOwner->setPath(*p);
	
		cout << "unit pathing" << endl;
	}
}
