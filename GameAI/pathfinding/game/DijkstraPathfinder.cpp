#include "DijkstraPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

DijkstraPathfinder::DijkstraPathfinder(Graph* graph)
: GridPathfinder(dynamic_cast<GridGraph*>(graph))
{
	#ifdef VISUALIZE_PATH
	mpPath = NULL;
	#endif
}

DijkstraPathfinder::~DijkstraPathfinder()
{
	#ifdef VISUALIZE_PATH
	delete mpPath;
	#endif
}

Path* DijkstraPathfinder::findPath(Node* fromNode, Node* toNode)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	
	//allocate nodes to open list and place starting node in it
	list<Node*> openNodes;
	openNodes.push_front(fromNode);
	
	//float minCost;

	#ifdef VISUALIZE_PATH
	delete mpPath;
	//empty out the closed list
	mVisitedNodes.clear(); 
	mVisitedNodes.push_back(fromNode);
	#endif

	//create Path
	Path* returnPath = new Path();

	Node* pCurrentNode = NULL;
	bool toNodeAdded = false;

	while (pCurrentNode != toNode && openNodes.size() > 0)
	{
		//get current node from front of open list
		pCurrentNode = openNodes.front();
		//remove node from open list
		openNodes.pop_front();
		//add Node to path
		returnPath->addNode(pCurrentNode);

		//get all the connections for the current node
		vector<Connection*> connections = mpGraph->getConnections(pCurrentNode->getId());

		//add all toNodes in the connections to the open list, if they are not already in the list
		for (unsigned int i = 0; i < connections.size(); i++)
		{
			Connection* tmpConnection = connections[i];
			Node* tmpToNode = connections[i]->getToNode();
			
			if (!toNodeAdded && !returnPath->containsNode(tmpToNode) &&
				find(openNodes.begin(), openNodes.end(), tmpToNode) == openNodes.end())
			{
				//nodesToVisit.push_front( pTempToNode );//uncomment me for depth-first search //make changeable at runtime?
				openNodes.push_back(tmpToNode);//uncomment me for breadth-first search

				//if temp node is the goal, stop adding to the open list
				if (tmpToNode == toNode)// && tmpConnection->getCost() < minCost)
				{
					toNodeAdded = true;
				}

				#ifdef VISUALIZE_PATH
				mVisitedNodes.push_back(tmpToNode);
				#endif

			}
		}
	}

	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

	#ifdef VISUALIZE_PATH
	mpPath = returnPath;
	#endif

	return returnPath;

}