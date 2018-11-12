#include "DijkstraPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include "MemoryTracker.h"
#include <PerformanceTracker.h>
#include <vector>
#include <algorithm>
#include "PriorityQueue.h"
#include "PathSmooth.h"


DijkstraPathfinder::DijkstraPathfinder(Graph* graph)
: GridPathfinder(dynamic_cast<GridGraph*>(graph))
{
	#ifdef VISUALIZE_PATH
	mpPath = NULL;
	#endif
}

DijkstraPathfinder::DijkstraPathfinder()
	: GridPathfinder(NULL)
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

	#ifdef VISUALIZE_PATH
	delete mpPath;
	mVisitedNodes.clear(); //empty out the visual list
	#endif

	Path* returnPath = new Path();	
	PriorityQueue <NodeRecord, vector<NodeRecord>, W_Compare> mOpenList, mClosedList;

	float endNodeCost;
	Node* endNode;
	NodeRecord currentRecord = {}, endNodeRecord = {};

	//init struct
	mNodeRecord = {};
	mNodeRecord.node = fromNode;
	mNodeRecord.connection = nullptr;
	mNodeRecord.costSoFar = 0;

	mOpenList.push(mNodeRecord);

	while (currentRecord.node != toNode && mOpenList.size() > 0)
	{
		//find smallest element
		currentRecord = mOpenList.top();
		mOpenList.pop();

		//display all visited nodes
//		returnPath->addNode(currentRecord.node);

		if (currentRecord.node == toNode)
			break;
		
		//collect & loop thru current node's connections
		vector<Connection*> connections = mpGraph->getConnections(currentRecord.node->getId());

		for (unsigned int i = 0; i < connections.size(); i++)
		{
			bool containedInClosedList = false, containedInOpenList = false;
			Connection* tmpConnection = connections[i];

			endNode = tmpConnection->getToNode();
			endNodeCost = currentRecord.costSoFar + tmpConnection->getCost();

			NodeRecord listCheck = {};
			PriorityQueue <NodeRecord, vector<NodeRecord>, W_Compare>::const_iterator it;

			listCheck.node = endNode;

			it = mOpenList.contains(listCheck);

			if (mClosedList.contains(listCheck) != mClosedList.end())
				continue;
			else if (it != mOpenList.end())
			{
				containedInOpenList = true;
				endNodeRecord.insert(it->node, it->connection, it->costSoFar);

				if (endNodeRecord.costSoFar <= endNodeCost)
					continue;
			}
			else
			{
				endNodeRecord = {};
				endNodeRecord.node = endNode;
			}

			endNodeRecord.costSoFar = endNodeCost;
			endNodeRecord.connection = tmpConnection;

			if(!containedInOpenList)
				mOpenList.push(endNodeRecord);

		}
		
		mClosedList.push(currentRecord);
		mVisitedNodes.push_back(currentRecord.node); //send to list for graphical visualization
		
	}
	
	if (currentRecord.node != toNode) //didn't reach goal
		return NULL;
	else
	{
		Path* path = new Path();

		while (currentRecord.node != fromNode)
		{
			path->addNode(currentRecord.node);

			currentRecord.node = currentRecord.connection->getFromNode();

			//find next connection in the closed list - traversing back to start
			PriorityQueue <NodeRecord, vector<NodeRecord>, W_Compare>::const_iterator it;

			it = mClosedList.contains(currentRecord);
			
			if(it != mClosedList.end())
				currentRecord.connection = it->connection;
		}

		int size = path->getNumNodes(); 
		for (int i = 0; i < size; i++) //reverse the path
		{
			returnPath->addNode(path->getAndRemoveNextNode());
		}

		#ifdef SMOOTH_PATH
		PathSmooth pathSmoother;
		returnPath = pathSmoother.smoothPath(returnPath);
		#endif

		delete path;
	}

	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

	#ifdef VISUALIZE_PATH
	mpPath = returnPath;
	#endif

	return returnPath;

}