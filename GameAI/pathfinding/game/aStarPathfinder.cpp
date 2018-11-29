#include "AStarPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include "GameApp.h"
#include "MemoryTracker.h"
#include <PerformanceTracker.h>
#include <vector>
#include <algorithm>
#include "PriorityQueue.h"


AStarPathfinder::AStarPathfinder(Graph* graph)
	: GridPathfinder(dynamic_cast<GridGraph*>(graph))
{
	#ifdef VISUALIZE_PATH
//	mpPath = NULL;
	#endif
}

AStarPathfinder::AStarPathfinder()
	: GridPathfinder(NULL)
{

#ifdef VISUALIZE_PATH
//	mpPath = NULL;
#endif
}

AStarPathfinder::~AStarPathfinder()
{
	#ifdef VISUALIZE_PATH
	delete mpPath;
	#endif
}

Path* AStarPathfinder::findPath(Node* fromNode, Node* toNode)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");

	#ifdef VISUALIZE_PATH
	delete mpPath;
	mVisitedNodes.clear();
	#endif

	Path* returnPath = new Path();
	PriorityQueue <NodeRecord, vector<NodeRecord>, W_AStarCompare> mOpenList, mClosedList;
	Node* endNode;
	NodeRecord currentRecord = {}, endNodeRecord = {};
	float endNodeHeurisitc, endNodeCost;

	mHeuristic.setGoal(toNode);

	//init struct
	mNodeRecord = {};
	mNodeRecord.node = fromNode;
	mNodeRecord.connection = nullptr;
	mNodeRecord.costSoFar = 0;
	mNodeRecord.estimatedTotalCost = mHeuristic.estimate(fromNode);

	mOpenList.push(mNodeRecord);

	while (currentRecord.node != toNode && mOpenList.size() > 0)
	{
		//find element with smallest estimated total cost
		currentRecord = mOpenList.top();
		mOpenList.pop();
		
		//display all visited nodes
		//returnPath->addNode(currentRecord.node);

		if (currentRecord.node == toNode)
			break;

		vector<Connection*> connections = mpGraph->getConnections(currentRecord.node->getId());

		for (unsigned int i = 0; i < connections.size(); i++)
		{
			bool containedInClosedList = false, containedInOpenList = false;
			Connection* tmpConnection = connections[i];

			endNode = tmpConnection->getToNode();
			endNodeCost = currentRecord.costSoFar + tmpConnection->getCost();

			NodeRecord tmpClosed = {};
			tmpClosed.node = endNode;

			PriorityQueue <NodeRecord, vector<NodeRecord>, W_Compare>::const_iterator it, it2;
			it = mClosedList.contains(tmpClosed);
 			it2 = mOpenList.contains(tmpClosed);

			if (it != mClosedList.end()) //node is w/in closed list, check if it needs to be revisited
			{
				endNodeRecord.insert(it->node, it->connection, it->costSoFar, it->estimatedTotalCost);
				if (endNodeRecord.costSoFar <= endNodeCost)
					continue;

				mClosedList.remove(endNodeRecord);

				endNodeHeurisitc = endNodeRecord.estimatedTotalCost - endNodeRecord.costSoFar;

			}
			else if (it2 != mOpenList.end()) //node is in open list already
			{
				containedInOpenList = true;

				endNodeRecord.insert(it2->node, it2->connection, it2->costSoFar, it2->estimatedTotalCost);				
				if (endNodeRecord.costSoFar <= endNodeCost)
					continue;

				endNodeHeurisitc = endNodeRecord.connection->getCost() - endNodeRecord.costSoFar;
			}
			else //unvisited node, make a record of it
			{
				endNodeRecord = {};
				endNodeRecord.node = endNode;
				endNodeHeurisitc = mHeuristic.estimate(endNode); //not toNode?
			}

			endNodeRecord.costSoFar = endNodeCost;
			endNodeRecord.connection = tmpConnection;
			endNodeRecord.estimatedTotalCost = endNodeCost + endNodeHeurisitc;

			if (!containedInOpenList)
				mOpenList.push(endNodeRecord);

		}

		mClosedList.push(currentRecord);
	//	mVisitedNodes.push_back(currentRecord.node);  //send to list for graphical visualization

	}

	if (currentRecord.node != toNode) //didn't reach goal
		return NULL;
	else
	{
		Path* path = new Path();

		while (currentRecord.node != fromNode) //traverse back to start to create path
		{
			path->addNode(currentRecord.node);

			currentRecord.node = currentRecord.connection->getFromNode();	

			PriorityQueue <NodeRecord, vector<NodeRecord>, W_Compare>::const_iterator it;
			it = mClosedList.contains(currentRecord);

			if (it != mClosedList.end())
				currentRecord.connection = it->connection;
		}
		int size = path->getNumNodes();
		for (int i = 0; i < size; i++)
		{
			//output optimal path
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
	GameApp* gpGameApp = dynamic_cast<GameApp*>(gpGame);
	//add path to paths to be visualized
	gpGameApp->gpPaths.push_back(returnPath);
	#endif

	return returnPath;
}