#include "DepthFirstPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

DepthFirstPathfinder::DepthFirstPathfinder( Graph* pGraph )
:GridPathfinder(dynamic_cast<GridGraph*>(pGraph) )
{
	#ifdef VISUALIZE_PATH
	mpPath = NULL;
	#endif

}

DepthFirstPathfinder::DepthFirstPathfinder()
	:GridPathfinder(NULL)
{
#ifdef VISUALIZE_PATH
	mpPath = NULL;
#endif

}

DepthFirstPathfinder::~DepthFirstPathfinder()
{
	#ifdef VISUALIZE_PATH
	delete mpPath;
	#endif
}

Path* DepthFirstPathfinder::findPath( Node* pFrom, Node* pTo )
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	//allocate nodes to visit list and place starting node in it
	list<Node*> nodesToVisit; //open list
	nodesToVisit.push_front( pFrom );

	#ifdef VISUALIZE_PATH
	delete mpPath;
	mVisitedNodes.clear(); //closed list
	mVisitedNodes.push_back( pFrom );
	#endif
	
	//create Path
	Path* pPath = new Path();

	Node* pCurrentNode = NULL;
	bool toNodeAdded = false;

	while( pCurrentNode != pTo && nodesToVisit.size() > 0 )
	{
		//get current node from front of open list
		pCurrentNode = nodesToVisit.front();
		//remove node from open list
		nodesToVisit.pop_front();
		//add Node to path
		pPath->addNode( pCurrentNode );

		//get all the connections for the current node
		vector<Connection*> connections = mpGraph->getConnections( pCurrentNode->getId() );

		//add all toNodes in the connections to the open list, if they are not already in the list
		for( unsigned int i=0; i < connections.size(); i++ )
		{
			Connection* pConnection = connections[i];
			Node* pTempToNode = connections[i]->getToNode();
			if( !toNodeAdded && !pPath->containsNode( pTempToNode ) && 
				find(nodesToVisit.begin(), nodesToVisit.end(), pTempToNode ) == nodesToVisit.end() )
			{
				nodesToVisit.push_front( pTempToNode );//uncomment me for depth-first search //make changeable at runtime?
				//nodesToVisit.push_back( pTempToNode );//uncomment me for breadth-first search
				
				//if node is the goal, stop adding to the open list
				if( pTempToNode == pTo )
				{
					toNodeAdded = true;
				}
				
				#ifdef VISUALIZE_PATH
				mVisitedNodes.push_back( pTempToNode );
				#endif

			}
		}
	}
	
	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

	#ifdef VISUALIZE_PATH
	mpPath = pPath;
	#endif
	
	return pPath;
}

